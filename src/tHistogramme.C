#include "../libs/ImageProcessingTools.h"

int main(void){
	PGM_PPM<rgb8> image;
	byte** matrix;
	ImageProcessingTools imageProcess;

	image.loadImage("../images/image.ppm");
	matrix = image.rgb8tobmatrix(image.matrix());

	imageProcess.histogramme(matrix, "image", image.nrl(), image.nrh(), image.ncl(), image.nch());

}