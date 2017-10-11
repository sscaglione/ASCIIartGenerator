/* translate.cpp */
#include "asciify.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <cstdlib>
#include <cstring>

//Version: ImageMagick 6.6.4-2 from ~ccl/software/external/imagemagick
#include <Magick++.h>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ofstream;

using namespace Magick;

// Prototype
void printArray(char translated[], int ht, int wd, ofstream &ofs);

/* Translates the source image file to the destination text file
 * Optional parameters can modify behavior
 * Parameters:
 * char* source -- Image source (either file or search term)
 * char* dest -- Output text file
 * int download -- Flag which determines if the file will be searched for and downloaded
 * int reimage -- Flag which indicates that after the text file is created, a JPEG version of that file should as well
 * Returns:
 * EXIT_SUCCESS (0) on success, EXIT_FAILURE (non-zero) otherwise
 */

int translate(char* source, char* dest, int download, int reimage){
	int exit_status = 0;
	char sysCall[BUFSIZ]; // Buffer for writing system calls
    char asciiConversionTable[256] = {0};     // Table that stores ascii characters corresponding to greyscale values 0-255

	/* Download image */
	if (download){
		cutExtension(source);
		cout << "Searching for " << source << "..." << endl;
		sprintf(sysCall, "python ./download.py '%s'", source);
		if (systemCall(sysCall)){
			return EXIT_FAILURE;
		}
		strcat(source, ".jpeg");
		cout << "Downloaded " << source << endl;
	}

    /* Generate ascii table */
    getAscii(asciiConversionTable);

	/* Create output file stream */
	ofstream ofs(dest, ofstream::trunc);

	/* Initialize ImageMagick API */
	InitializeMagick(PROGRAM_NAME);

	/* Construct the image object. Separating construction from reading
	 * ensures failure to read doesn't render the object useless */
	Image image;
	try {
		int w, h, range; // Width, height, range
		int row, col; // Used for iteration

		Color val; // Holds individual pixel values

		/* Read a file into image object */
		image.read(source);
		
		/* Get Image height and width */
		w = image.columns();
		h = image.rows();
	
		/* Get range from 0 to 255 (versus ~65,000) */
		range = pow(2, image.modulusDepth());
		assert(range > 0);

		/* Get pixel array */
		PixelPacket *pixels = image.getPixels(0, 0, w, h);
		
		/* Write ASCII values to output file */
		cout << "Converting " << source << " to text...";
        int greyvals[w * h] = {0};        // Image greyscale values
        char translated[w * h] = {0};     // Image ascii chars
		for (row = 0; row < h; ++row){
			for(col = 0; col < w; ++col){
                val = pixels[w * row + col];        // Color of pixel
                int red = val.redQuantum() / range;
                int green = val.greenQuantum() / range;
                int blue = val.blueQuantum() / range;

                // Calculated greyscale value - weighted average of RGB values
                int grey = (RED_WT * red) + (GREEN_WT * green) + (BLUE_WT * blue);
				
                // Add to greyvals
                greyvals[(row * h) + col] = grey;

                // Convert to ascii
                convert(greyvals, translated, asciiConversionTable, w * h);

                /* Convert to ASCII and write */
				//val = pixels[(w * row) + col];
				/* Calculate weighted average with constants weighting color channels */
				//weighted_average = ( (RED_WT * val.redQuantum()) / range ) + ( (GREEN_WT * val.greenQuantum()) / range ) + ( (BLUE_WT * val.blueQuantum()) / range );
				//ascii_val = grayAscii(round(weighted_average));
				//ofs << ascii_val;
			}
			//ofs << endl; // End of row
		}
        printArray(translated, h, w, ofs);
		cout << "done (" << dest  << ')' << endl;

		if (reimage){
			char* dest_reimage = strdup(dest); // Need a copy because cutExtension modifies its argument
			cutExtension(dest_reimage);
            
            /* Create image to convert to */
            
			/* System call to ImageMagick program to convert ASCII text to image */
            sprintf(sysCall, "touch %s.jpeg", dest_reimage);
            //sprintf(sysCall, "convert %s -font DejaVu-Sans-Mono-Book -fill black label:@%s %s.jpeg", dest, dest, dest_reimage);
			sprintf(sysCall, "%s -font DejaVu-Sans-Mono-Book -fill black label:@%s %s.jpeg  ", CONVERT_PATH, dest, dest_reimage);
			cout << "Converting " << dest << " to JPEG...";
			if (systemCall(sysCall)){
				exit_status = EXIT_FAILURE;
			}
            else{
				cout << "done (" << dest_reimage << ".jpeg)" << endl;
			}
			free(dest_reimage);
		}
  	}catch( Exception &error_ ){ 
	      cerr << "Caught exception: " << error_.what() << endl;
		  exit_status = EXIT_FAILURE;
	}
	
	ofs.close();
	return exit_status;
}

/* Generates a table of 256 characters corresponding to 256 greyscale values
 * Parameters:
 * int g_value -- An integer value between [0, 255] representing a gray pixel value
 */
void getAscii(char asciiChars[256]){
    // black->white ascii character ramp
	char ramp[70] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*',
							'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm',
							'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
							'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't',
							'/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',
							'?', '-', '_', '+', '~', '<', '>', 'i', 'l', '!',
							'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '};
    int rampindex = 0;
    int greyval = 0;

    while (greyval < 255){      // 255 possible greyscale values are represented by 70 ascii chars
        // Assign 46 characters to greyscale values 0 - 183
        // 4 values to 1 character
        if (greyval < 184){ 
            for (int i = 0; i < 4; i++){
                asciiChars[greyval] = ramp[rampindex];
                greyval++;
            }
        }

        // Assign remainning 24 charcteres to greyscale values 184 - 255
        // 3 values to 1 character
        if (greyval >= 184){
            for (int i = 0; i < 3; i++){
                asciiChars[greyval] = ramp[rampindex];
                greyval++;
            }
        }
        
        // Iterate to next character to be asigned to greyvals
        rampindex++;
    }
    return;
}

// Generate ascii characters corresponding to image's greyscale values
void convert(int greys[], char translated[], char asciiChars[256], int size){
    for (int i = 0; i < size; i++){
        translated[i] = asciiChars[greys[i]];
    }

    return;
}

/* Makes a system call
 * Prints an error message if the call fails
 * Parameters:
 * const char* call -- The C-string representation of the command to call
 * Returns:
 * 0 on success, non-zero on failure
 */
int systemCall(const char* call){
	int status = system(call);
	if (status){
		cerr << "System call '" << call << "' returned non-zero exit status" << endl;
	}
	return status;
}


/* Removes the extension from a filename
 * This modifies the original filename string
 * Parameters:
 * char* filename -- The name of the file to remove the extension form
 * Returns:
 * void
 */
void cutExtension(char* filename){
	/* Reverse iterate for first instance of '.' */
	for (int i = strlen(filename); i > 0; --i){
		if (filename[i] == '.'){
			filename[i] = '\0';
			return;
		}
	}
	return;
}

/* Writes ascii chars to file
 * char translated[] - ascii characters for image
 * int ht - height of image
 * int wd - width of image
 * ostream ofs - file stream
 */
void printArray(char translated[], int ht, int wd, ofstream &ofs){
    for (int i = 0; i < (ht * wd); i++){
        ofs << translated[i];
        if ((i + 1) % wd == 0){
            ofs << endl;
        }
    }

    return;
}
