#include <Magick++.h>
#include <iostream>
using namespace std;
using namespace Magick;
int main(int argc,char **argv)
{
  InitializeMagick(*argv);

  // Construct the image object. Separating image construction from the
  // the read operation ensures that a failure to read the image file
  // doesn't render the image object useless.
  Image image;
  try {
    // Read a file into image object
    image.read( "sample.jpeg" );

    image.quantizeColorSpace( GRAYColorspace );
    image.quantizeColors( 256 );
    image.quantize( );

    // Write the image to a file
    image.write( "bwsample.jpeg" );
  }
  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  return 0;
}
