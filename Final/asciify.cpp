#include <iostream>
#include <cstdlib> // Macros, memory allocation, system calls
#include <cstring> // String duplication
#include <unistd.h> // POSIX OS API, argument parsing

#include "asciify.h"

using std::endl;
using std::cin;
using std::cout;
using std::cerr;
using std::ofstream;

/* Global variables */
char* PROGRAM_NAME;

/* Usage function */
void usage(int status){
	cerr << "Usage:\t" << PROGRAM_NAME << "[options] Image [output file]" << endl;
	cerr << "\t-h\tDisplay this usage message" << endl;
	cerr << "\t-s\tSearch for Image with Google search" << endl;
	cerr << "\t-j\tConvert output text to .jpeg file" << endl;
	exit(status);
}

/* Main execution */
int main(int argc, char **argv){	
	PROGRAM_NAME = argv[0];

	int exit_status;
	int download = 0; // Flag, download image or not
	int reimage = 0; // Flag, convert text to .jpeg
	
	/* Argument parsing */
	int opt;
	while ( (opt = getopt(argc, argv, "hsj")) != -1){
		switch(opt){
			case 'h':
				usage(EXIT_SUCCESS);
				break;
			case 's':
				download = 1;				
				break;
			case 'j':
				reimage = 1;
				break;
			default:
				usage(EXIT_FAILURE);
		}
	}

	if (optind >= argc){
		usage(EXIT_FAILURE);
	}

	char* image_arg = new char[strlen(argv[optind]) + 6];
	image_arg[0] = '\0'; // Ensure concatenation from first character
	strcat(image_arg, argv[optind]);
	++optind;

	/* Output file */
	char* f_name;
	if (argc > optind){
		f_name = strdup(argv[optind]);
	}else{
		f_name = strdup("output.txt"); // Default name
	}

	/* Translate image */
	exit_status = translate(image_arg, f_name, download, reimage);

	delete[] image_arg;
	free(f_name);
	return exit_status; 
}
