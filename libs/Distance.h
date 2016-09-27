#ifndef __DISTANCE
#define __DISTANCE

#include <math.h>
#include "PGM_PPM.h"

class Distance {

    protected:
        int _length;

    public:
        Distance(int length){_length = length;}
        double euclidian (long* histo1, long *histo2);
        double Bhattacharyyas(long* histo1, long *histo2); 
        double BhattacharyyasCoef(long* histo1, long *histo2);
        double sum(long* hist);

};

#endif
