#include "../libs/Distance.h"
#include "../libs/ImageProcessingTools.h"

int main () {

	PGM_PPM<rgb8> image1, image2;
    byte **matrix1;
    byte **matrix2;
    Distance distances(256);

	image1.loadImage("../images/1.ppm");
	image2.loadImage("../images/2.ppm");
	matrix1 = image1.rgb8tobmatrix(image1.matrix());
	matrix2 = image2.rgb8tobmatrix(image2.matrix());

	long* histogram1 = histogramme(matrix1, image1.nrl(), image1.nrh(), image1.ncl(), image1.nch());
	long* histogram2 = histogramme(matrix2, image2.nrl(), image2.nrh(), image2.ncl(), image2.nch());

    double bhatacharyyasCoef = distances.BhattacharyyasCoef(histogram1, histogram2);
    double bhatacharyyas = distances.Bhattacharyyas(histogram1, histogram2);
    double euclidian = distances.euclidian(histogram1, histogram2);

    cout << "Euclidian : " << endl;
    cout << "distance : " << euclidian << endl << endl;

    cout << "Bhattacharyyas : " << endl;
    //cout << "coef : " << bhatacharyyasCoef << endl;
    cout << "distance : " << bhatacharyyas << endl;


    return 0;
}
