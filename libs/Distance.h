#ifndef __DISTANCE
#define __DISTANCE

#include <math.h>

class Distance {

    protected:
        int _length;

    public:
        Distance(int length){_length = length;}
        double euclidian (int* histo1, int *histo2);
        double Bhattacharyyas(int* histo1, int *histo2); 
        double BhattacharyyasCoef(int* histo1, int *histo2);
        double Distance::sum(byte* hist);

}
