#include <Magick++.h> 
#include <iostream> 
#include<math.h>
#include <assert.h>
using namespace std; 
using namespace Magick; 
int main(int argc,char **argv) 
{ 
  InitializeMagick(argv[0]);

  // Construct the image object. Separating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Image image;
  try { 
    // Read a file into image object 
    image.read( "dc7ecbd73238c26897ce67b3a52dd8fe.jpg" );


	//Version 6 API
	//Version: ImageMagick 6.6.4-2 running on AFS network (??)
	//Trying to get pixels
	//ColorGray val;
	Color val;
	int w = image.columns();
	int h = image.rows();
	int row = 0;
	int col = 0;
	
	//Without this range, the image values were like 65553
	//Get correct range from 0 to 256
	int range = pow(2, image.modulusDepth());
	//cout << image.modulusDepth() << endl;
	assert(range>0);
	//cout << range;
	
	PixelPacket *pixels = image.getPixels(0, 0, w, h);
	val = pixels[w * row + col];
	//Print out values for all of the pixels in the image
	for (row = 0; row<h-1; row++) {
		for(col = 0; col<w-1;col++) {
			val = pixels[w*row+col];
			cout << "val: " << (val.redQuantum()/range) << endl;
		}
	}

	
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
