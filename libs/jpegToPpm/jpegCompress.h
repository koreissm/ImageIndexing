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



#ifndef jpegCOMPRESS_H
#define jpegCOMPRESS_H

#include <iostream>
#include <cstdlib>
#include "jpegStream.h"

#ifdef __cplusplus
extern "C" {
#endif 
#include <jpeglib.h>
#ifdef __cplusplus
}
#endif 

#define jpeg_COMPRESS_BUFFER_SIZE 4096

namespace jpeg {
  class Compress { 

  public:

  private: 
 
    OStream* output; 
    OStdStream std_output;

    JOCTET jpg_buf[jpeg_COMPRESS_BUFFER_SIZE];
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    struct jpeg_destination_mgr mout;

    static void init_destination(j_compress_ptr cinfo) {
      cinfo->dest->next_output_byte
	=(JOCTET*)(((jpeg::Compress*)(cinfo->client_data))->jpg_buf); 
      cinfo->dest->free_in_buffer=jpeg_COMPRESS_BUFFER_SIZE;
    }

    static boolean empty_output_buffer (j_compress_ptr cinfo) {
      jpeg::Compress* that = (jpeg::Compress*)(cinfo->client_data); 
      that->output->writeBytes((char*)(that->jpg_buf),jpeg_COMPRESS_BUFFER_SIZE);
      init_destination(cinfo);
      return TRUE;
    }

    static void term_destination(j_compress_ptr cinfo) {
      jpeg::Compress* that = (jpeg::Compress*)(cinfo->client_data); 
      that->output->writeBytes((char*)(that->jpg_buf),
			       (size_t)(
					(long int)(cinfo->dest->next_output_byte)
					- (long int)(that->jpg_buf)));
    }

  public:

    Compress(void) {
      output = (OStream*)NULL;
      cinfo.err=jpeg_std_error(&jerr);
      jpeg_create_compress(&cinfo);
      
      mout.init_destination=jpeg::Compress::init_destination;
      mout.empty_output_buffer=jpeg::Compress::empty_output_buffer;
      mout.term_destination=jpeg::Compress::term_destination;
      cinfo.dest=&mout;
      cinfo.client_data = (void*)this;
    };
    
    ~Compress(void) {
      jpeg_destroy_compress(&cinfo);
    }

    /**
     * Set the output stream the jpeg file is written in. It has to be
     * correctly opened.
     */
    void setOutputStream(std::ostream& os) { 
      
      std_output.setStream(os);
      output = &std_output; 
    }  

    /**
     * Set the output stream the jpeg file is written in. It just need
     * to be inherited from jpeg::Decompress::Stream interface. 
     */
    void setOutputStream(OStream* os) {
      output = os;
    }

    /**
     * This writes the jpeg file.
     * @param width image width.
     * @param height image height.
     * @param depth 3 for color, 1 for grayscale.
     * @param img_buf the rgbrgbrgb.... or gggggggg.... data line by line(according to depth).
     * @param quality in [1-100]
     */
    void writeImage(int width, int height, int depth,
		    unsigned char* img_buf,int quality=75) {
      
      unsigned char* row;                 /* Store adress of the first element of the current row */
      size_t row_stride;                  /* depth*width */

      
      cinfo.image_width=width;
      cinfo.image_height=height;
      cinfo.input_components=depth;
      if(depth==1)
	cinfo.in_color_space=JCS_GRAYSCALE;
      else
	cinfo.in_color_space=JCS_RGB;
      jpeg_set_defaults(&cinfo);
      jpeg_set_quality(&cinfo,quality,TRUE);

      row_stride=width*depth;
      jpeg_start_compress(&cinfo,TRUE);
      while(cinfo.next_scanline<cinfo.image_height)
	{
	  row=img_buf+(cinfo.next_scanline*row_stride);
	  (void) jpeg_write_scanlines(&cinfo,&row,1);
	}
      jpeg_finish_compress(&cinfo);
    }
  };
}

#endif
