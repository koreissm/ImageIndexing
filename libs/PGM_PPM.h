#ifndef __PGM_PPM
#define __PGM_PPM

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <ctype.h>

#include "./jpegToPpm/jpeg-c++.h"

#define NR_END 1

using namespace std;

typedef unsigned char byte;
typedef struct { byte r; byte g; byte b;}rgb8;

template <typename T>
class PGM_PPM{ 
	protected:
		T** _matrix;
		long _nrl; //1ere ligne
		long _nrh; //Nombre de lignes
		long _ncl; //1ere colonne
		long _nch; //Nombre de colonnes
	
	public:
		PGM_PPM(){};
		PGM_PPM(long nrl, long nrh, long ncl, long nch){_nrl=nrl; _nrh=nrh; _ncl=ncl; _nch=nch;};
		void loadImage(char* filename);
		void loadJpeg(char* filename);
		void saveImage(T** matrix, char* filename);
		T** buildMatrix();
		char* _readitem(ifstream& file, char* buffer);
		long nrl(){ return _nrl;};
		long nrh(){ return _nrh;};
		long ncl(){ return _ncl;};
		long nch(){ return _nch;};
		T** matrix(){ return _matrix;};
		byte** rgb8tobmatrix(rgb8** m);
};

#include "PGM_PPM.C"
#endif
