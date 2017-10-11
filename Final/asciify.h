#ifndef ASCIIFY_H
#define ASCIIFY_H

/* Useful Macros */
#define CONVERT_PATH "/afs/nd.edu/user37/ccl/software/external/imagemagick/bin/convert"
#define RED_WT 0.2989
#define GREEN_WT 0.5870
#define BLUE_WT 0.1140

/* Global variables */
extern char* PROGRAM_NAME;

/* Translation methods */
int translate(char* source, char* dest, int download, int reimage);
int systemCall(const char* call);
//char grayAscii(int g_value);
void cutExtension(char* filename);
void convert(int greys[], char translated[], char asciiChars[256], int size);
void getAscii(char asciiChars[256]);

#endif
