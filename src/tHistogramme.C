#include "../libs/ImageProcessingTools.h"

int main(void){
	PGM_PPM<rgb8> image;
	byte** matrix;

	image.loadImage("../images/image.ppm");
	matrix = image.rgb8tobmatrix(image.matrix());

	long*h = histogramme(matrix, image.nrl(), image.nrh(), image.ncl(), image.nch());
    for (int i = 0; i < 256; i++)
        cout << i << " : " << h[i] << endl;
}
