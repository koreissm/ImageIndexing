#include"Distance.h"
#include "ImageProcessingTools.h"
#include <algorithm>
#include <map>

#define SEUIL 0.2

char** Distance::getSimilarImages (char* baseImageName) {

	PGM_PPM<rgb8>* images = new PGM_PPM<rgb8>[500];
    PGM_PPM<rgb8> baseImage;
    byte ***matrix = new byte**[500];
    byte **baseMatrix;
    Distance distances(256);
    float* distanceArray = new float[500];
    std::map <float, char*> distanceMap;
    char** finalImages = new char*[5];

    baseImage.loadJpeg(baseImageName);
	baseMatrix = baseImage.rgb8tobmatrix(baseImage.matrix());
	long* baseHistogram = histogramme(baseMatrix, baseImage.nrl(), baseImage.nrh(), baseImage.ncl(), baseImage.nch());
    float basePercentage = percentageOfContoursInImageTrue(baseMatrix, baseImage.nrl(), baseImage.nrh(), baseImage.ncl(), baseImage.nch());
    cout << "Base Image : " << basePercentage << endl << endl;
        
    for (int i = 1; i <= 500; i++) {
        char *buffer = new char[80];
        sprintf(buffer, "../big_imagesJPG/%d.jpg", i);
	    images[i].loadJpeg(buffer);

	    matrix[i] = images[i].rgb8tobmatrix(images[i].matrix());

	    long* histogram = histogramme(matrix[i], images[i].nrl(), images[i].nrh(), images[i].ncl(), images[i].nch());

        float bhatacharyyas = distances.Bhattacharyyas(baseHistogram, histogram);
        //float percentage = percentageOfContoursInImageTrue(matrix[i], images[i].nrl(), images[i].nrh(), images[i].ncl(), images[i].nch());

        //cout << "Image " << i << " : " << percentage << endl;
       
        distanceMap[bhatacharyyas] = buffer;
        //distanceMap[bhatacharyyas] = i;
        //distanceArray[i] = percentage;

        //float euclidian = distances.euclidian(histogram3, histogram4);
        //cout << "Euclidian : " << endl;
        //cout << "distance : " << euclidian << endl << endl;

        //cout << "Bhattacharyyas : " << endl;
        //cout << "distance : " << bhatacharyyas << endl;
    }


    int number = 0;
    for (std::map<float, char*>::iterator i = distanceMap.begin(); i != distanceMap.end(); i++) {
        if (number == 5) break;
        finalImages[number] = i->second;
        number++;
    }

    return finalImages;
}

float Distance::euclidian (long* h1, long *h2) {
    long long distance = 0;

    for (int i = 0; i < _length; i++) {
        distance += pow((h1[i]-h2[i]), 2);
    }

    return sqrt(distance); 
}

//Calculate Bhattacharyya's distance between two histogramss
float Distance::Bhattacharyyas(long* h1, long *h2) {
    return -log(BhattacharyyasCoef(h1, h2));
}

//Bhattacharyya's coefficient
float Distance::BhattacharyyasCoef(long* h1, long *h2) {
    float coef = 0;
    float sum1 = sum(h1), sum2 = sum(h2);

    for (int i = 0; i < _length; i++) {
        coef += sqrt((h1[i] * h2[i]) / (sum1 * sum2));
    }

    return coef;
}

float Distance::sum(long* hist) {
   float s = 0; 
    for (int i = 0; i < _length; i++) {
        s += (float) hist[i];
    }
    return s;
}
