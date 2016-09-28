#include "ImageProcessingTools.h"

PGM_PPM<byte> apply_mask(int(* mask)[3], byte** matrix, long nrl, long nrh, long ncl, long nch){
	PGM_PPM<byte> imageM(nrl, nrh, ncl, nch); //image après le masque
	float tmp;
	imageM.buildMatrix();


	for(int i = nrl+1; i < nrh ; i++) {
		for(int j = ncl+1; j < nch ; j++){

			tmp = 0;
			
			tmp = (matrix[i+1][j+1]*mask[0][0]) + (matrix[i+1][j]*mask[0][1])
				+ (matrix[i+1][j-1]*mask[0][2])

				+ (matrix[i][j+1]*mask[1][0]) + (matrix[i][j]*mask[1][1])
				+ (matrix[i][j-1]*mask[1][2])
				
				+ (matrix[i-1][j+1]*mask[2][0]) + (matrix[i-1][j]*mask[2][1])
				+ (matrix[i-1][j-1]*mask[2][2]);
				
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

long* histogramme(byte** matrix, long nrl, long nrh, long ncl, long nch){
	long* hist = new long[256];

	for(int i=0; i<256; i++)
		hist[i]=0;

	for(long i=nrl; i<nrh; i++){
		for(long j=ncl; j<nch; j++){
			hist[matrix[i][j]]++;
		}
	}
	
	return hist;
}

float percentageOfContoursInImage(byte** matrix, long nrl, long nrh, long ncl, long nch) {
    float nb;
    int totalPixels = nrh * nch;    
    for (int i = 0; i < nrh; i++) {
        for (int j = 0; j < nch; j++) {
            if (matrix[i][j] == 255)
                nb++;
        }
    }

    return nb / totalPixels;
}

float* rateColors(rgb8** matrix, long nrl, long nrh, long ncl, long nch){
	long nb_pixels = nrh*nch;

	float* rate_colors = new float[5]; // red, green, blue, white, black
     
    rate_colors[0]=0;rate_colors[1]=0;rate_colors[2]=0;rate_colors[3]=0;rate_colors[4]=0;

	for(long i=nrl; i<nrh; i++){
		for(long j=ncl; j<nch; j++){
			if(matrix[i][j].r>SEUIL_MAX && (matrix[i][j].g+matrix[i][j].b) < SEUIL_OTHERS){
				rate_colors[0]++;
			} else if(matrix[i][j].g>SEUIL_MAX && (matrix[i][j].r+matrix[i][j].b) < SEUIL_OTHERS){
				rate_colors[1]++;
			} else if(matrix[i][j].b>SEUIL_MAX && (matrix[i][j].r+matrix[i][j].g) < SEUIL_OTHERS){
				rate_colors[2]++;
			} else if(matrix[i][j].r>SEUIL_W && matrix[i][j].g>SEUIL_W && matrix[i][j].b>SEUIL_W){
				rate_colors[3]++;
			} else if(matrix[i][j].r<SEUIL_B && matrix[i][j].g<SEUIL_B && matrix[i][j].b<SEUIL_B){
				rate_colors[4]++;
			}
		}
	}

	for(int i=0; i<5; i++){
		float f = ((float)rate_colors[i]/(float)nb_pixels)*100.0;
		rate_colors[i] = f;
		//cout << rate_colors[i] << endl;
	}
    return rate_colors;
}

float percentageOfContoursInImageTrue(byte** matrix, long nrl, long nrh, long ncl, long nch) {
    PGM_PPM<byte> img_sobelx;
    PGM_PPM<byte> img_sobely;
    PGM_PPM<byte> norme;

    int filtreSobelX[][3] =  {
	    {-1, 0, 1},
	    {-2, 0, 2},
	    {-1, 0, 1}
    };

    int filtreSobelY[][3] =  {
	    {-1, -2, -1},
	    {0, 0, 0},
  	    {1, 2, 1}
    };

    img_sobelx = apply_mask(filtreSobelX, matrix, nrl, nrh, ncl, nch);
    img_sobely = apply_mask(filtreSobelY, matrix, nrl, nrh, ncl, nch);

    norme = binariser(normeGradient(img_sobelx.matrix(), img_sobely.matrix(), nrl, nrh, ncl, nch).matrix(), nrl, nrh, ncl, nch, SEUIL_BINARISATION);

    norme.saveImage(norme.matrix(), "../outputs/norme.pgm");
    
    return percentageOfContoursInImage(norme.matrix(), nrl, nrh, ncl, nch);
}

void processImage(char* path, char* filename, char* outPath){
	PGM_PPM<rgb8> image;
	byte** mat;
	long* hist;
	float* rate_colors;
	float percentageOfContours;

	image.loadJpeg(path);
	mat = image.rgb8tobmatrix(image.matrix());

	ofstream outputFile;
	char* outputFile_name = new char[80];
	char* buffer = new char[80];

	sprintf(outputFile_name, "%s%s.txt",outPath, filename);
	
	outputFile.open(outputFile_name);
	if (!outputFile.is_open())
    	cerr << "ouverture du fichier output impossible" << endl;

	hist = histogramme(mat, image.nrl(), image.nrh(), image.ncl(), image.nch());
	rate_colors = rateColors(image.matrix(), image.nrl(), image.nrh(), image.ncl(), image.nch());
	percentageOfContours = percentageOfContoursInImageTrue(mat, image.nrl(), image.nrh(), image.ncl(), image.nch());


	sprintf(buffer,"%f", percentageOfContours);
	outputFile.write(buffer, strlen(buffer));

	sprintf(buffer,"\n%f", rate_colors[0]);
	outputFile.write(buffer, strlen(buffer));
	for(int i=1; i<5; i++){
		sprintf(buffer,";%f", rate_colors[i]);
		outputFile.write(buffer, strlen(buffer));
	}

	sprintf(buffer,"\n%ld", hist[0]);
	outputFile.write(buffer, strlen(buffer));
	for(int i=1; i<255; i++){
		sprintf(buffer,";%ld", hist[i]);
		outputFile.write(buffer, strlen(buffer));
	}
    
    outputFile.close();
}
