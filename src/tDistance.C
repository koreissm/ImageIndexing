#include "../libs/Distance.h"
#include "../libs/ImageProcessingTools.h"


int main() {
    Distance distance(256);
    char* baseImageName = "../big_imagesJPG/71.jpg";
    char ** similarImages = distance.getSimilarImages(baseImageName);
    for (int i = 0; i < 5; i++) {
        printf("%s\n", similarImages[i]);
    }

    return 0;
}
