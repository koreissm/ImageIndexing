#include "Mask.h"

PGM_PPM<byte> Mask::apply_mask(byte** matrix, long nrl, long nrh, long ncl, long nch){
	PGM_PPM<byte> imageM(nrl, nrh, ncl, nch); //image après le masque
	double tmp;
	imageM.buildMatrix();


	for(int i = nrl+1; i < nrh ; i++)
		for(int j = ncl+1; j < nch ; j++){

			tmp = 0;
			
			for(int u = -1; u < 2 ; u++)
				for(int v = -1; v < 2 ; v++){
					tmp += matrix[i-u][j-v]*_mask[u+1][v+1];
				}
			imageM.matrix()[i][j] = (fabs(tmp)/1020)*255;
		}

	return imageM;
}