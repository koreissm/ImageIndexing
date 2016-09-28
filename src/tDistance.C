#include "../libs/Distance.h"
#include "../libs/ImageProcessingTools.h"

int main () {

	PGM_PPM<rgb8> image1, image2, image3, image4;
    byte **matrix1;
    byte **matrix2;
    byte **matrix3;
    byte **matrix4;
    Distance distances(256);

	image1.loadJpeg("../imagesJPG/vache1.jpg");
	image2.loadJpeg("../imagesJPG/vache3.jpg");
	image3.loadJpeg("../imagesJPG/mer1.jpg");
	image4.loadJpeg("../imagesJPG/arbre2.jpg");

	matrix1 = image1.rgb8tobmatrix(image1.matrix());
	matrix2 = image2.rgb8tobmatrix(image2.matrix());
	matrix3 = image3.rgb8tobmatrix(image3.matrix());
	matrix4 = image4.rgb8tobmatrix(image4.matrix());

	long* histogram1 = histogramme(matrix1, image1.nrl(), image1.nrh(), image1.ncl(), image1.nch());
	long* histogram2 = histogramme(matrix2, image2.nrl(), image2.nrh(), image2.ncl(), image2.nch());
	long* histogram3 = histogramme(matrix3, image3.nrl(), image3.nrh(), image3.ncl(), image3.nch());
	long* histogram4 = histogramme(matrix4, image4.nrl(), image4.nrh(), image4.ncl(), image4.nch());

    double bhatacharyyas = distances.Bhattacharyyas(histogram1, histogram2);
    double euclidian = distances.euclidian(histogram1, histogram2);

    cout << "Euclidian : " << endl;
    cout << "distance : " << euclidian << endl << endl;

    cout << "Bhattacharyyas : " << endl;
    cout << "distance : " << bhatacharyyas << endl;


    return 0;
}
