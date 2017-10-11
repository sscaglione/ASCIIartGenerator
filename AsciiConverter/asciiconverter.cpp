/* 4/19/17; CSE 20312 - Data Structures
 * asciiconverter.cpp
 * Convert image from greyscale values to ascii characters
 */

#include <Magick++.h>
#include "functions.cpp"
#include <iostream>
#include <math.h>       // int range
using namespace std;
using namespace Magick;

int main(int argc, char **argv){
    char ascii[256];        // Indices = greyscale values; elements = corresponding ascii chars
    string file = "smile.jpg";
    
    // Create greyscale -> ascii lookup table
    getASCII(ascii);

    // Initialize Magick++
    InitializeMagick(*argv);

    // Construct image object, checking that file exists
    Image image;
    try{
        // Read a file into image object
        image.read(file);
    }
    catch (Exception &error_){
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }

    // Get image height, width, pixels
    int width = image.columns();
    int height = image.rows();
    int size = width * height;      // Number of pixels in image
    int grays[size];        // Greyscale values in image
    char translation[size];      // Ascii chars representing image
    int range = pow(2, image.modulusDepth());       // Gets values in correct 0-256 range

    // Iterate over pixels in image
    // ***NEW FUNCTION -> getGrays???***
    PixelPacket *pixels = image.getPixels(0, 0, width, height);
    Color pixel;        // Individual pixel color values
    int p = 0;      // Pixel index; keeps track of number of grey values
    for (int row = 0; row < height; row++){
        for (int col = 0; col < width; col++){
            // Get pixel's RGB values
            pixel = pixels[width * row + col];      // ***What exactly is width*row+col?***
            int red = pixel.redQuantum() / range;
            int green = pixel.greenQuantum() / range;
            int blue = pixel.blueQuantum() / range;

            // Use weights on RGB vals to get pixel's grayscale value
            // *** SOURCE WEIGHTS ***
            int gray = (0.2989 * red) + (0.5870 * green) + (0.1140 * blue);
            
            // Add greyscale value to array of greyscale values
            grays[p] = gray;
            p++;
        }
    }

    // Convert greyscale values to ascii characters
    translate(grays, translation, ascii, size);

    // Print ascii - iterate over translation
    for (int i = 0; i < size; i++){
        cout << translation[i];
        if (i % width == 0){
            cout << endl;
        }
    }

    return 0;
}
