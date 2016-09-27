#ifndef __IMAGE_PROCESSING_TOOLS
#define __IMAGE_PROCESSING_TOOLS

#include "PGM_PPM.h"
#include <math.h>

#define SEUIL_MAX 100
#define SEUIL_OTHERS 200
#define SEUIL_W 150
#define SEUIL_B 50

class ImageProcessingTools{

protected:
	int (* _mask)[3];

public:
	ImageProcessingTools(){};
	ImageProcessingTools(int (* mask)[3]){_mask = mask;};
	PGM_PPM<byte> apply_mask(byte** matrix, long nrl, long nrh, long ncl, long nch);
	PGM_PPM<byte> normeGradient(byte** sobelX, byte** sobelY, long nrl, long nrh, long ncl, long nch);
    PGM_PPM<byte> binariser(byte** matrix, long nrl, long nrh, long ncl, long nch, int seuil);
	long* histogramme(byte** matrix, char* filename, long nrl, long nrh, long ncl, long nch);
    double purcentageOfContoursInImage(byte** matrix, long nrl, long nrh, long ncl, long nch); 
	long* rateColors(rgb8** matrix, long nrl, long nrh, long ncl, long nch);
};

#include "ImageProcessingTools.C"
#endif
