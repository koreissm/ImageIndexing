
PGM_PPM<byte> Mask::apply_mask(byte** matrix, long nrl, long nrh, long ncl, long nch){
	PGM_PPM<byte> imageM(nrl, nrh, ncl, nch); //image après le masque
	double tmp;
	imageM.buildMatrix();


	for(int i = nrl+1; i < nrh ; i++) {
		for(int j = ncl+1; j < nch ; j++){

			tmp = 0;
			
			for(int u = -1; u < 2 ; u++)
				for(int v = -1; v < 2 ; v++){
					tmp += matrix[i-u][j-v]*_mask[u+1][v+1];
				}
			imageM.matrix()[i][j] = (fabs(tmp)/1020)*255;
		}
    }

	return imageM;
}


PGM_PPM<byte> normeGradient(byte** sobelX, byte** sobelY, long nrl, long nrh, long ncl, long nch) {
	PGM_PPM<byte> imageM(nrl, nrh, ncl, nch); //image après le masque
	imageM.buildMatrix();

    for(int i = nrl+1; i < nrh ; i++) {
		for(int j = ncl+1; j < nch ; j++){
            imageM.matrix()[i][j] = sqrt(sobelX[i][j] * sobelX[i][j] + sobelY[i][j] * sobelY[i][j]);
        }
    }

    return imageM;
}

PGM_PPM<byte> binariser(byte** matrix, long nrl, long nrh, long ncl, long nch, int seuil) {
    PGM_PPM<byte> imageM(nrl, nrh, ncl, nch); //image après le masque
	imageM.buildMatrix();

    for(int i = nrl+1; i < nrh ; i++) {
		for(int j = ncl+1; j < nch ; j++){
            if (matrix[i][j] < seuil)
                imageM.matrix()[i][j] = 0;
            else
                imageM.matrix()[i][j] = 255;
        }
    }
    return imageM;
}
