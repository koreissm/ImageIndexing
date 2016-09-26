#include "Mask.h"

int main(void){
  PGM_PPM<byte> img;
  PGM_PPM<rgb8> img1;

  PGM_PPM<byte> img_sobelx;
  PGM_PPM<byte> img_sobely;

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

  img.loadImage("./images/image.pgm");
  img.saveImage(img.matrix(), "./images/copie_image.pgm");

  img1.loadImage("./images/nuit.ppm");
  img1.saveImage(img1.matrix(), "./images/copie_nuit.ppm");

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

  img_sobelx.saveImage(img_sobelx.matrix(), "./images/image_sobelx.pgm");

  img_sobely.saveImage(img_sobely.matrix(), "./images/image_sobely.pgm");

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

  img_sobelx.saveImage(img_sobelx.matrix(), "./images/nuit_sobelx.pgm");

  img_sobely.saveImage(img_sobely.matrix(), "./images/nuit_sobely.pgm");

}
