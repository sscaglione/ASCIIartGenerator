/* Amy Byrnes; 3/12/17; CSE 20312 - Data Structures
 * magicktest.cpp
 * Based on code in magick++ api
 */

#include <Magick++.h>
#include <iostream>
using namespace std;
using namespace Magick;

int main(int argc, char **argv){ 
    InitializeMagick(*argv);

    //  Construct the image object. Seperating image construction from the
    //  read operation ensures that a failure to read the image file
    //  doesn't render the image object useless.
    Image image;
    try{
        // Read a file into image object
        image.read("spongebob.jpg");

        // Crop the image to specified size (width, height, xOffset, yOffset)
        image.crop(Geometry(100,100,100,100));

        // Write the image to a file
        image.write("spongebob2.jpg");

    }
    catch (Exception &error_){
        cout << "Caught exception: " << error_.what() << endl;
        return 1;
    }

    return 0;
}

