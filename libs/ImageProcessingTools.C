
PGM_PPM<byte> ImageProcessingTools::apply_mask(byte** matrix, long nrl, long nrh, long ncl, long nch){
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

long* ImageProcessingTools::histogramme(byte** matrix, char* filename, long nrl, long nrh, long ncl, long nch){
	long* hist = new long[255];
	ofstream file;

	char* buffer = new char[80];

	sprintf(buffer, "hist_%s", filename);

	file.open(buffer);
  	if (!file.is_open())
    	cerr << "ouverture du fichier impossible" << endl;

	for(int i=0; i<255; i++)
		hist[i]=0;

	for(long i=nrl; i<nrh; i++){
		for(long j=ncl; j<nch; j++){
			hist[matrix[i][j]]++;
		}
	}

	for(int i=0; i<255; i++){
		sprintf(buffer,"%d %ld\n", i, hist[i]);
		file.write(buffer, strlen(buffer));
	}

	file.close();
	return hist;
}

double purcentageOfContoursInImage(byte** matrix, long nrl, long nrh, long ncl, long nch) {
    double nb;
    int totalPixels = nrh * nch;    
    for (int i = 0; i < nrh; i++) {
        for (int j = 0; j < nch; j++) {
            if (matrix[i][j] == 255)
                nb++;
        }
    }

    return nb / totalPixels;
}
