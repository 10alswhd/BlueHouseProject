#include <stdio.h>

int screenWidth = 150;
int screenHeight = 51;

int main() {
}

int naiveSearch(int numImages, int minWidth, int maxWidth) {
    for(int i=maxWidth; i>=minWidth; i--) {
        // assume square images
        if (check(numImages, i, i))
            return i;
    }
}

int check(int numImages, int imageWidth, int imageHeight) {
    for(int i=1; i<numImages; i++) {
        int numImagesPerRow = numImages / imageWidth;
        int pixelHeight = numImagesPerRow * imageHeight;
        if (pixelHeight <= screenHeight) {
            return 1; //true
        }
    }
    return 0; // false
}
