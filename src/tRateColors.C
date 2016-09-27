#include "../libs/ImageProcessingTools.h"

int main(void){
	PGM_PPM<rgb8> image;

	image.loadImage("../images/2.ppm");

	rateColors(image.matrix(), image.nrl(), image.nrh(), image.ncl(), image.nch());

}