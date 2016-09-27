#include "../libs/ImageProcessingTools.h"

int main(void){
  PGM_PPM<byte> img;
  PGM_PPM<rgb8> img1;

  PGM_PPM<byte> img_sobelx;
  PGM_PPM<byte> img_sobely;
  PGM_PPM<byte> norme;


  int filtreMoyenneur[][3] =  {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
  };

 int filtreSobelX[][3] =  {
	{-1, 0, 1},
	{-2, 0, 2},
	{-1, 0, 1}
  };

  int filtreSobelY[][3] =  {
	{-1, -2, -1},
	{0, 0, 0},
  	{1, 2, 1}
  };

  Mask sobelx(filtreSobelX);
  Mask sobely(filtreSobelY);

  img.loadImage("../images/1.pgm");
  img.saveImage(img.matrix(), "../outputs/1.pgm");

  img1.loadImage("../images/1.ppm");
  img1.saveImage(img1.matrix(), "../outputs/1.ppm");

  img_sobelx = sobelx.apply_mask(img.matrix(), 
  	img.nrl(),
  	img.nrh(),
  	img.ncl(),
  	img.nch()
  );

  img_sobely = sobely.apply_mask(img.matrix(), 
  	img.nrl(),
  	img.nrh(),
  	img.ncl(),
  	img.nch()
  );

  img_sobelx.saveImage(img_sobelx.matrix(), "../outputs/image_sobelx.pgm");

  img_sobely.saveImage(img_sobely.matrix(), "../outputs/image_sobely.pgm");

  img_sobelx = sobelx.apply_mask(img1.rgb8tobmatrix(img1.matrix()), 
  	img1.nrl(),
  	img1.nrh(),
  	img1.ncl(),
  	img1.nch()
  );

  img_sobely = sobely.apply_mask(img1.rgb8tobmatrix(img1.matrix()), 
  	img1.nrl(),
  	img1.nrh(),
  	img1.ncl(),
  	img1.nch()
  );

  img_sobelx.saveImage(img_sobelx.matrix(), "../outputs/nuit_sobelx.pgm");

  img_sobely.saveImage(img_sobely.matrix(), "../outputs/nuit_sobely.pgm");

  int seuil = 20;
  norme = binariser(normeGradient(img_sobelx.matrix(), img_sobely.matrix(), img_sobelx.nrl(), img_sobelx.nrh(), img_sobelx.ncl(), img_sobelx.nch()).matrix(), img_sobelx.nrl(), img_sobelx.nrh(), img_sobelx.ncl(), img_sobelx.nch(), seuil);
  norme.saveImage(norme.matrix(), "../outputs/norme.pgm");
}
