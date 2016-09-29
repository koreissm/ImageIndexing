#ifndef __DISTANCE
#define __DISTANCE

#include <math.h>
#include "PGM_PPM.h"

class Distance {

    protected:
        int _length;

    public:
        Distance(int length){_length = length;}
        float euclidian (long* histo1, long *histo2);
        float Bhattacharyyas(long* histo1, long *histo2); 
        float BhattacharyyasCoef(long* histo1, long *histo2);
        float sum(long* hist);
        char** getSimilarImages (char* baseImageName);
};

#endif
