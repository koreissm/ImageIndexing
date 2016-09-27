#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def.h"
#include "nrio.h"
#include "nralloc.h"
#include "nrarith.h"


// Filtrage Passe Bas (Moyenneur) - Question 3
byte** filtrage (byte** Image,long nrl,long nrh,long ncl,long nch){

	byte** imageFiltrage = NULL;
	imageFiltrage = bmatrix(nrl,nrh,ncl,nch);
	long i =0 ,j=0;
	long sum ;

	for (i=nrl+1; i<nrh; i++){
		for (j=ncl+1; j<nch; j++){
			sum =  Image[i-1][j-1] + Image[i-1][j] + Image[i-1][j+1] +
				Image[i][j-1] + Image[i][j]+ Image[i][j+1] +
				Image[i+1][j-1] + Image[i+1][j] + Image[i+1][j+1] ;
			imageFiltrage[i][j] = sum/9; 

	
		}
	}
	
	return imageFiltrage;

}

// Sobel Horizontal - Question 4.1
byte** SobelHorizontal (byte** Image,long nrl,long nrh,long ncl,long nch){

	byte** imageSobel = NULL;
	imageSobel = bmatrix(nrl,nrh,ncl,nch);

	long i =0 ,j=0;
	long sum ;

	for (i=nrl+1; i<nrh; i++){
		for (j=ncl+1; j<nch; j++){
			sum = (-1 * Image[i-1][j-1]) + Image[i-1][j+1] 
				+ (-2 * Image[i][j-1]) + (2 * Image[i][j+1]) 
				+ (-1 * Image[i+1][j-1]) + Image[i+1][j+1];

			imageSobel[i][j]= (fabs(sum)/1020)*255;
		}
	}
	
	return imageSobel;

}

// Sobel Vertical - Question 4.2
byte** SobelVertical (byte** Image,long nrl,long nrh,long ncl,long nch){

	byte** imageSobel = NULL;
	imageSobel = bmatrix(nrl,nrh,ncl,nch);

	long i =0 ,j=0;
	long sum ;

	for (i=nrl+1; i<nrh; i++){
		for (j=ncl+1; j<nch; j++){
			sum = (-1 * Image[i-1][j-1]) + (-2 * Image[i-1][j]) + (-1 * Image[i-1][j+1])   
				+ Image[i+1][j-1] + (2 * Image[i+1][j]) + Image[i+1][j+1];

			imageSobel[i][j]= (fabs(sum)/1020)*255;
		}
	}
	
	return imageSobel;

}

/* Question 2 - Lecture et ecriture d'une image */

int main (int argc, char ** argv){

	byte** matriceImage = NULL;
	byte** imageFiltrage = NULL;
	byte** imageSobelH = NULL;
	byte** imageSobelV = NULL;

	long nrl; // 1 ère ligne
	long nrh; // nombre de lignes 
	long ncl; // 1 ere colonne
	long nch; // nombre de colonnes

	matriceImage = LoadPGM_bmatrix("./imagetp/ppm/cubesx3.pgm", &nrl, &nrh, &ncl,&nch);

	//SavePGM_bmatrix(matriceImage, nrl, nrh, ncl, nch, "./premiereImage.pgm");

	//Question 3
	//imageFiltrage = filtrage(matriceImage,nrl,nrh,ncl,nch);
	//SavePGM_bmatrix(imageFiltrage, nrl, nrh, ncl, nch, "./imageFiltragePasseBas.pgm");
	//free_bmatrix(imageFiltrage,nrl, nrh, ncl, nch);

	//Question 4.1 Sobel Horizontal
	imageSobelH = SobelHorizontal(matriceImage,nrl,nrh,ncl,nch);
	SavePGM_bmatrix(imageSobelH, nrl, nrh, ncl, nch, "./sobelHorizontal.pgm");
	free_bmatrix(imageSobelH,nrl, nrh, ncl, nch);

	//Question 4.2 Sobel Vertical
	imageSobelV = SobelVertical(matriceImage,nrl,nrh,ncl,nch);
	SavePGM_bmatrix(imageSobelV, nrl, nrh, ncl, nch, "./sobelVertical.pgm");
	free_bmatrix(imageSobelV,nrl, nrh, ncl, nch);

	free_bmatrix(matriceImage,nrl, nrh, ncl, nch);
	
	

	return 0;

}








