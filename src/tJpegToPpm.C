#include "../libs/ImageProcessingTools.h"

int main(void){
	PGM_PPM<rgb8> image;

	image.loadJpeg("../imagesJPG/arbre1.jpg");
	image.saveImage(image.matrix(), "test.ppm");
}