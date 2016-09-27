#include "../libs/ImageProcessingTools.h"

int main(void){
	PGM_PPM<rgb8> image;
	ImageProcessingTools imageProcess;

	image.loadImage("../images/2.ppm");

	imageProcess.rateColors(image.matrix(), image.nrl(), image.nrh(), image.ncl(), image.nch());

}