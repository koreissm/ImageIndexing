#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "jpeg-c++.h"
#include "../PGM_PPM.h"

using namespace std;

int main(int argc, char* argv[]) {

  std::ostringstream jpeg_in_memory;
  std::ostringstream filename;
  jpeg::Decompress jpg_to_bytes(jpeg_in_memory);  
  int width,height,depth,size;  
  unsigned char* img_buffer;  
  std::ifstream foo;  
  std::ofstream bar;
  char c;
  int no;


  if(argc<5) {
    std::cout << "Usage :" << std::endl
	      << "  " << argv[0] << " <mjpeg-file> <prefix> <nb_digits> <first-number>" << std::endl;
    return 0;
  }

  foo.open(argv[1]);
  if(!foo)
    {
      std::cerr << "Cannot read \"" << argv[1] << "\" file. Aborting." << std::endl;
      return 1;
    }
  jpg_to_bytes.setInputStream(foo); 


  img_buffer=NULL;

  foo.get(c);
  no=atoi(argv[4]);

  while(!foo.eof()) {
    foo.putback(c);

    jpeg_in_memory.seekp(0);

    try
      {
	jpg_to_bytes.readHeader(width,height,depth);
  cout << "taille img : " << depth << endl;
	size = width*height*depth;

	delete [] img_buffer;

  img_buffer = new unsigned char[size];
  jpg_to_bytes.readImage(img_buffer);

  if (depth == 3){
    PGM_PPM<rgb8> imagePPM((long) 0, (long) height-1, (long) 0, (long) width-1);
    rgb8 **m;
    int line=0, col=0;

    m = imagePPM.buildMatrix();
    for (int i = 0; i < size; i+=3){
      rgb8 buffer_rgb;

      buffer_rgb.r = img_buffer[i];
      buffer_rgb.g = img_buffer[i+1];
      buffer_rgb.b = img_buffer[i+2];
      m[line][col]=buffer_rgb;

      col++;
      if(col == width){
        line++;
        col = 0;
      }
    }

    imagePPM.saveImage(m, "image.ppm");

  } else {
    PGM_PPM<byte> imagePPM((long) 0, (long) height, (long) 0, (long) width);
    byte **m;

    int line=0, col=0;

    m = imagePPM.buildMatrix();
    for (int i = 0; i < size; i++){
      m[line][col]=buffer_rgb[i];
      
      col++;
      if(col == width){
        line++;
        col = 0;
      }
    }
  }

	filename.clear();
	filename.seekp(0);
	filename << argv[2] << "-" << std::setw(atoi(argv[3])) << std::setfill('0')
		 << no << ".jpg";

	bar.clear();
	bar.open(filename.str().c_str());
	if(!bar)
	  std::cout << "Cannot open \"" << filename.str() << "\"." << std::endl;
	else {
	  bar.write(jpeg_in_memory.str().c_str(),jpeg_in_memory.tellp());
	  bar.close();
	  std::cout << "File " << filename.str() << " generated." << std::endl;
	}
      }
    catch(jpeg::exception::Any e)
      {
	std::cout << "Skipping corrupted frames at frame " << no << std::endl;
	no --;
	jpg_to_bytes.SkipToNextImage();
	jpg_to_bytes.ClearErrors();
      }
    foo.get(c);
    no++;
  }
  

  return 0;

}
