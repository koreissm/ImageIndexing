#include"Distance.h"

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
