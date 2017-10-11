#include <Magick++.h> 
#include <iostream> 
#include<math.h>
#include <assert.h>
#include<string.h>
using namespace std; 
using namespace Magick; 

char grayAscii(int g_value) {
		char ascii[] = { '$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*', 
						'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
						'z', 'c', 'v', 'u', 'n','x', 'r', 'j', 'f', 't',
						'/', '\\','|', '(', ')', '1', '{', '}', '[', ']', 
						'\?', '-', '_', '+', '~', '<', '>', 'i','!', 'l',
						'I', ';',':', ',', '\"', '^', '`', '\'', '.', '?'
					
		};
	//if ascii array is ordered from lightest to darkest then it would correctly go to the correct bucket 
	//The darkest ascii char is 0 and lightest is 255
	int ind_value = (g_value)/ (256/70);
		
//If grey value is 254 254 / (256/70) = 69...
//So it should pick up what is the index 69
return ascii[ind_value];
}
//
void translate(int greys[], char tran[], int size) {
	
	char ramp[] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*',
					'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm',
					'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
					 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't',
					 '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',
					 '?', '-', '_', '+', '~', '<', '>', 'i', 'l', '!',
					 'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '}; 
	//Ascii char, dark->light
	char ascii[256];
	int rampval = 0;
	int greyval = 0;


	while(greyval < 255) {
		if (greyval < 184) {
			for (int i = 0; i < 4; i++) {
				ascii[greyval] = ramp[rampval];
				greyval++;
			}
		} else {
			for (int i = 0; i < 3;i++) {
				ascii[greyval] = ramp[rampval];
				greyval++;
			}
		}
		rampval++;
	}

	//TRANSLATE GREYSCALE VALUES TO ASCII CHARACTERS
	for (int i = 0; i < size; i++){
		tran[i] = ascii[greys[i]];
	}
	
	return;
};

void printArray(char greys[], int ht, int wd) {
	for (int i = 0; i < (ht*wd); i++) {
		cout << greys[i]; 
		if (((i+1) % wd) == 0) cout << endl;
	}
}
int main(int argc,char **argv) 
{ 
  InitializeMagick(*argv);

  // Construct the image object. Separating image construction from the 
  // the read operation ensures that a failure to read the image file 
  // doesn't render the image object useless. 
  Image image;
  try { 
    // Read a file into image object
	string image_to_read = argv[1];
    image.read(image_to_read);


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
	//A 1D array of grey scale values
	int greyvals[w*h]; 
	char translated[w*h];

	for (row = 0; row<h; row++) {
		for(col = 0; col<w;col++) {
			val = pixels[w*row+col];
			int red = val.redQuantum()/ range;
			int green = val.greenQuantum()/range;
			int blue = val.blueQuantum()/range;

			//Convert to Grayscale values with weights given to each color
			int gray = 0.2989 * red + 0.5870 * green + 0.1140 * blue;
			greyvals[(row*h) + col] = gray;
			
		}
	}
	
	translate(greyvals, translated, w*h);
	printArray(translated, h, w);	
		
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
