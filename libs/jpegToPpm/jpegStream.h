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
#include <iostream>


#ifndef jpegSTREAM_H
#define jpegSTREAM_H

namespace jpeg {

  /**
   * Inherit from this class to allow jpeg decompression from data.
   */ 
  class IStream {
  public:
    IStream(void) {};
    virtual ~IStream(void) {};

    /**
     * Tries to read nb_to_read bytes, and stores them in a large
     * enough byte buffer dest_buf.
     */
    virtual void readBytes(char* dest_buf,int nb_to_read)=0;

    /**
     * Returns the number of bytes actually read by last readBytes call.
     */
    virtual int countReadBytes(void)=0;
  };

  /**
   * This allow the management of std::istream object.
   */
  class IStdStream : public IStream {
  private :
      
    std::istream* input; 

  public:
      
    IStdStream(void) : IStream(), input(NULL) {};
    virtual ~IStdStream(void) {};

    void setStream(std::istream& is) {input = &is;} 
    virtual void readBytes(char* dest_buf,int nb_to_read) {
      input->read(dest_buf,nb_to_read);
    }

    virtual int countReadBytes(void) {
      return (int)(input->gcount());
    }
  };

  /**
   * Inherit from this class to allow jpeg decompression from data.
   */ 
  class OStream {
  public:
    OStream(void) {};
    virtual ~OStream(void) {};

    /**
     * writes nb_to_read bytes.
     */
    virtual void writeBytes(char* src_buf,int nb_to_write)=0;
  };

  /**
   * This allow the management of std::istream object.
   */
  class OStdStream : public OStream {
  private :
      
    std::ostream* output; 

  public:
      
    OStdStream(void) : OStream(), output(NULL) {};
    virtual ~OStdStream(void) {};

    void setStream(std::ostream& os) {output = &os;} 
    
      
    virtual void writeBytes(char* src_buf,int nb_to_write) {
      output->write(src_buf,nb_to_write);
    }
      
  };


}

#endif
