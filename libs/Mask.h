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
};
#endif