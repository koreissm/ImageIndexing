#ifndef __IMAGE_PROCESSING_TOOLS
#define __IMAGE_PROCESSING_TOOLS

#include "PGM_PPM.h"
#include <math.h>

#define SEUIL_MAX 100
#define SEUIL_OTHERS 200
#define SEUIL_W 150
#define SEUIL_B 50
#define SEUIL_BINARISATION 20

PGM_PPM<byte> apply_mask(int(* mask)[3], byte** matrix, long nrl, long nrh, long ncl, long nch);
PGM_PPM<byte> normeGradient(byte** sobelX, byte** sobelY, long nrl, long nrh, long ncl, long nch);
PGM_PPM<byte> binariser(byte** matrix, long nrl, long nrh, long ncl, long nch, int seuil);
double percentageOfContoursInImage(byte** matrix, long nrl, long nrh, long ncl, long nch); 
long* histogramme(byte** matrix, long nrl, long nrh, long ncl, long nch);
float* rateColors(rgb8** matrix, long nrl, long nrh, long ncl, long nch);
void processImage(char* path, char* filename, char* outPath);
double percentageOfContoursInImageTrue(byte** matrix, long nrl, long nrh, long ncl, long nch);
    
#endif
