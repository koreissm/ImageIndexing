#ifndef __MASK
#define __MASK

#include "PGM_PPM.h"
#include <math.h>

class Mask{

protected:
	int (* _mask)[3];

public:
	Mask(int (* mask)[3]){_mask = mask;};
	PGM_PPM<byte> apply_mask(byte** matrix, long nrl, long nrh, long ncl, long nch);
	byte** normeGradient(byte** sobelX, byte** sobelY, long nrl, long nrh, long ncl, long nch);
    byte** binariser(byte** matrix, long nrl, long nrh, long ncl, long nch, int seuil);
	byte hist[255] histogramme(byte** matrix, long nrl, long nrh, long ncl, long nch);
};

#include "ImageProcessingTools.C"
#endif
