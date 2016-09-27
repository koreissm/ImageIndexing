#include "../libs/Mask.h"

int main(void){
	PGM_PPM<rgb8> image;
	byte** matrix;

	long hist[255];
	ofstream file;

	char* buffer = new char[80];

	file.open("result");
  	if (!file.is_open())
    	cerr << "ouverture du fichier impossible" << endl;

	for(int i; i<255; i++)
		hist[i]=0;

	image.loadImage("../images/image.ppm");
	matrix = image.rgb8tobmatrix(image.matrix());

	for(long i=image.nrl(); i<image.nrh(); i++){
		for(long j=image.ncl(); j<image.nch(); j++){
			hist[matrix[i][j]]++;
		}
	}

	sprintf(buffer,"image.ppm\n");
	file.write(buffer, strlen(buffer));
	for(int i; i<255; i++){
		sprintf(buffer,"%d %ld\n", i, hist[i]);
		file.write(buffer, strlen(buffer));
	}

	file.close();

}