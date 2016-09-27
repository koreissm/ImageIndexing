/*

  Copyright (c) 2006,  Herve Frezza-Buet, Supelec
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

    * Redistributions of source code must retain the above copyright 
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in 
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Supelec nor the names of its contributors 
      may be used to endorse or promote products derived from this 
      software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

*/



#ifndef jpegDECOMPRESS_H
#define jpegDECOMPRESS_H

#include <iostream>
#include <cstdlib>
#include "jpegStream.h"
#include "jpegException.h"

#ifdef __cplusplus
extern "C" {
#endif 
#include <jpeglib.h>
#ifdef __cplusplus
}
#endif 


#define jpeg_DECOMPRESS_BUFFER_SIZE 4096
#define jpeg_START_OF_MARKER 255
#define jpeg_START_OF_IMAGE 216

namespace jpeg {

  class Decompress { 

  private: 
 
    IStream* input; 
    IStdStream std_input;
    OStream* jpeg_copy;
    OStdStream std_jpeg_copy;

    struct my_error_mgr {
      struct jpeg_error_mgr pub;
    };

    struct my_src_mgr {
      struct jpeg_source_mgr pub; 
      jpeg::Decompress* that;
    };

    struct my_error_mgr jerr;
    struct my_src_mgr src;
    struct jpeg_decompress_struct cinfo;
    JOCTET jpg_buf[jpeg_DECOMPRESS_BUFFER_SIZE];
    int row_stride;

    void CopyBuffer(void) {
      if(jpeg_copy!=NULL)
	jpeg_copy->writeBytes((char*)(src.pub.next_input_byte),
			      src.pub.bytes_in_buffer);

    }

    static void init_source(j_decompress_ptr cinfo) {
      ((struct my_src_mgr*)(cinfo->src))->that->initSource();
    }
    
    void initSource(void) {
      CopyBuffer();
    }

    static boolean fill_input_buffer(j_decompress_ptr cinfo) {
      return ((struct my_src_mgr*)(cinfo->src))->that->fillInputBuffer();
    }

    boolean fillInputBuffer(void) {
      input->readBytes((char*)jpg_buf,jpeg_DECOMPRESS_BUFFER_SIZE);
      src.pub.next_input_byte = jpg_buf;
      src.pub.bytes_in_buffer = input->countReadBytes();

      CopyBuffer();

      return TRUE;
    }

    static void skip_input_data(j_decompress_ptr cinfo, long num_bytes) {
      ((struct my_src_mgr*)(cinfo->src))->that->skipInputData(num_bytes);
    }
    
    void skipInputData(long num_bytes) {
      
      if (num_bytes > 0) {
	while (num_bytes > (long) src.pub.bytes_in_buffer) {
	  num_bytes -= (long) src.pub.bytes_in_buffer;
	  (void) fillInputBuffer();
	}
	src.pub.next_input_byte += (size_t) num_bytes;
	src.pub.bytes_in_buffer -= (size_t) num_bytes;
      }
    }

    static void term_source(j_decompress_ptr) {
    }

    static void on_exit (j_common_ptr) {      
      throw exception::OnExit();
    }

    static void on_format (j_common_ptr, char* msg) {
      throw exception::OnFormat(msg);
    }

    static void on_output (j_common_ptr) {
      throw exception::OnOutput();
    }

    static void on_emit (j_common_ptr,int) {
      throw exception::OnEmit();
    }

  private:
    
    void InitJPEG(void) {
//       jerr.pub.format_message = on_format;
//       jerr.pub.output_message = on_output;
//       jerr.pub.emit_message = on_emit;

      cinfo.err = jpeg_std_error(&jerr.pub);
      jerr.pub.error_exit = on_exit;
      jpeg_create_decompress(&cinfo);
      cinfo.src = (jpeg_source_mgr*)(&src);
      src.that = this;

      src.pub.init_source = init_source;
      src.pub.fill_input_buffer = fill_input_buffer;
      src.pub.skip_input_data = skip_input_data;
      src.pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
      src.pub.term_source = term_source;
      src.pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
      src.pub.next_input_byte = NULL; /* until buffer loaded */
    }

  public:

    enum BufferStatus {
      internalFailedEmpty,   //!< The procedure fails to find delimiter, so the buffer is now empty.
      internalFoundEmpty,    //!< Delimiter has been found, removed, and now the buffer is empty.
      internalFoundNotEmpty  //!< Delimiter has been found, removed, but there is still bytes in the buffer.
    };
    typedef enum BufferStatus BufferStatus;

    Decompress(void) {
      jpeg_copy=(OStream*)NULL;
      input=(IStream*)NULL;
      InitJPEG();
    }

    /**
     * This decompressor will copy the jpeg file in a copy stream. If
     * this stream is a ostringstream, you can have a raw jpeg image
     * stored in memory.
     */
    Decompress(std::ostream& copy) {
      std_jpeg_copy.setStream(copy);
      jpeg_copy = &std_jpeg_copy;
      InitJPEG();
    }

    /**
     * This decompressor will copy the jpeg file in a copy
     * stream. <b>copy may be deleted internally, it meust have been
     * allocated with new.</b>
     */
    Decompress(OStream* copy) {
      jpeg_copy=copy;
      InitJPEG();
    }

    ~Decompress(void) {
      jpeg_destroy_decompress(&cinfo);
    } 

    
    /**
     * Set the stream to which the jpeg source will be copied. NULL
     * disables copy.
     */
    void setCopyStream(OStream* copy) {
      jpeg_copy=copy;
    }

    /**
     * Set the stream to which the jpeg source will be copied. 
     */
    void setCopyStream(std::ostream& copy) {
      std_jpeg_copy.setStream(copy);
      jpeg_copy = &std_jpeg_copy;
    }
  
    /**
     * Set the output stream the jpeg files comes from. It has to be
     * correctly opened.
     */
    void setInputStream(std::istream& is) { 
      std_input.setStream(is);
      input = &std_input;
    }  
    
    /**
     * Set the output stream the jpeg files comes from. It has to be
     * correctly opened. <b>is may be deleted internally, it must have
     * been allocated with new.</b>
     */
    void setInputStream(jpeg::IStream* is) { 
      input = is; 
    }  

    /**
     * When decompressing, first call this method, that tells you
     * information about the file, and thus the image buffer size.
     * @param width,height image size. Be sure your destination buffer is big enough.
     * @param depth is 1(gray) or 3(rgb) : this is the number of bytes per pixel.
     */
    void readHeader(int& width,int& height,
		    int& depth) {
      // std::cout << " First byte :" << (int)((unsigned char)(*(src.pub.next_input_byte))) << std::endl;  

      (void) jpeg_read_header(&cinfo,TRUE);
      (void) jpeg_start_decompress(&cinfo);

      depth = cinfo.output_components;
      width = cinfo.output_width;
      height = cinfo.output_height;
      
      row_stride = width*depth;
    }
  

    /**
     * Call readHeader once before calling this method.
     * @param img_buf an array of width*height*depth bytes.
     */
    void readImage(unsigned char* img_buf) {
      unsigned char* row;

      for(row = img_buf;
	  cinfo.output_scanline < cinfo.output_height;
	  row += row_stride)
	(void) jpeg_read_scanlines(&cinfo,&row,1);
      (void) jpeg_finish_decompress(&cinfo);
    }

    /**
     * Flushes internal buffer. be sure that what is in there isn't
     * the beginning of a next jpeg image.
     */
    void Flush(void) {
      src.pub.bytes_in_buffer=0;
    }


    /**
     * This rebuilds the whole jpeg-lib decompression stuff.
     */
    void ReBuild(void) {
      jpeg_destroy_decompress(&cinfo);
      InitJPEG();
    }

    /**
     * This clears errors.
     */
    void ClearErrors(void) {

      // Make a backup of some contents still important in the buffer
      int old_position = src.pub.bytes_in_buffer;
      const JOCTET * old_next_input_byte = src.pub.next_input_byte;
      jpeg_destroy_decompress(&cinfo);
      
      cinfo.err = jpeg_std_error(&jerr.pub);
      jerr.pub.error_exit = on_exit;
      jpeg_create_decompress(&cinfo);
      cinfo.src = (jpeg_source_mgr*)(&src);
      src.that = this;

      src.pub.init_source = init_source;
      src.pub.fill_input_buffer = fill_input_buffer;
      src.pub.skip_input_data = skip_input_data;
      src.pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
      src.pub.term_source = term_source;
      src.pub.bytes_in_buffer = old_position;
      src.pub.next_input_byte = old_next_input_byte; 
    }



    

    /**
     * Eats some bytes from the input stream.
     * @param num the number of bytes to skip.
     */
    void Skip(long num) {
      skipInputData(num);
    }

    /**
     * Eats bytes in the internal buffer until delimiter is found, or
     * internal buffer is empty. 
     * @param delimiter the delimiter
     * @param extracted is true if the delimiter is removed from the stream.
     */
    BufferStatus FlushUntil(char delimiter,bool extracted=true) {
      bool not_found;
      BufferStatus res;

      for(not_found=true;
	  src.pub.bytes_in_buffer>0 && not_found;
	  src.pub.next_input_byte++,src.pub.bytes_in_buffer--) 
	not_found = ((char)(*src.pub.next_input_byte))!=delimiter;

      if(not_found)
	res = internalFailedEmpty;
      else if(src.pub.bytes_in_buffer==0) {
	if(extracted)
	  res = internalFoundEmpty; 
	else {
	  // put back delimiter
	  src.pub.next_input_byte--;
	  src.pub.bytes_in_buffer++;
	  res = internalFoundNotEmpty;
	}
      }
      else {
	if(!extracted) {
	  // put back delimiter
	  src.pub.next_input_byte--;
	  src.pub.bytes_in_buffer++;
	}
	res = internalFoundNotEmpty;
      }

      return res;
    }

    /**
     * Skips the content of the buffer until reaching the delimiter of the next image
     */
    void SkipToNextImage(void)
    {
      while(FlushUntil((char)jpeg_START_OF_MARKER, false) == internalFailedEmpty)
	{
	  fillInputBuffer();
	  if(input->countReadBytes() == 0)
	    throw jpeg::exception::EmptyInputStream();
	}
      // The buffer starts with 0xFF
      if(src.pub.bytes_in_buffer >= 2)
	  if(*(src.pub.next_input_byte+1) == jpeg_START_OF_IMAGE)
	    return;
	  else
	    {
	      FlushUntil((char)jpeg_START_OF_MARKER, true);
	      SkipToNextImage();
	    }
      else
	{
	  src.pub.next_input_byte--;
	  jpg_buf[jpeg_DECOMPRESS_BUFFER_SIZE-2] = jpeg_START_OF_MARKER;
	  src.pub.bytes_in_buffer = 2;
	  input->readBytes((char*)(src.pub.next_input_byte+1),1);
	  SkipToNextImage();
	}
    }
  };
}

#endif
