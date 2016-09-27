#include"Distance.h"

double Distance::euclidian (long* h1, long *h2) {
    int distance = 0;

    for (int i = 0; i < _length; i++) {
        distance += (h1-h2) * (h1-h2);
    }

    return sqrt(distance); 
}

//Calculate Bhattacharyya's distance between two histogramss
double Distance::Bhattacharyyas(long* h1, long *h2) {
    return -log(BhattacharyyasCoef(h1, h2));
}

//Bhattacharyya's coefficient
double Distance::BhattacharyyasCoef(long* h1, long *h2) {
    double coef = 0;
    double sum1 = sum(h1), sum2 = sum(h2);

    for (int i = 0; i < _length; i++) {
        coef += sqrt((h1[i] * h2[i]) / (sum1 * sum2));
    }

    return coef;
}

double Distance::sum(long* hist) {
   double s = 0; 
    for (int i = 0; i < _length; i++) {
        s += (double) hist[i];
    }
    return s;
}
