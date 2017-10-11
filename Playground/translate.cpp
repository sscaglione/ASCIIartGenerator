/* Amy Byrnes; 3/21/17; CSE 20312 - Data Structures
 * translate.cpp
 * Translate an array of integer values to ascii characters using lookup table and case statement
 */

#include <iostream>
using namespace std;

int main(){
    int length = 256;       // = 20
    int greys[length];     //= {0, 56, 200, 102, 42, 90, 232, 67, 58, 24,
                    //122, 125, 127, 255, 1, 216, 189, 13, 244, 101};     // Greyscale values
    for (int i = 0; i < length; i++){
        greys[i] = i;
    }

    char ascii[70] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*',
                        'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm',
                        'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
                        'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't',
                        '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',
                        '?', '-', '_', '+', '~', '<', '>', 'i', 'l', '!',
                        'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '};      // Ascii chars used; dark->light
    char translated[length];     // Array of translated greyscale values
    int asciipos = 0;       // Position of char in ascii array

    for (int i = 0; i < length; i++){
        // Groupings of 3 or 4 greyscale values = 1 ascii char
        int grouping = 3;       // Highest grey val in grouping; 0-3, 4-7, etc.
        int aval = 0;      // Index of ascii array corresponding to grouping

        // Iterate over groupings, incrementing aval until correct one is found
        while (grouping <= 255){
            if (greys[i] <= grouping){
                asciipos = aval;
                cout << greys[i] << " " << grouping << " " << asciipos << endl;
                break;
            }
            
            aval++;

            if (grouping < 182){
                grouping += 4;      // 44 groups of 4 values corresponding to 1 ascii char
            }
            else if (grouping <= 252){
                grouping += 3;      // 32 groups of 3 values corresponding to 1 ascii char
            }
            else{
                grouping = 255;
            }
        }       

        translated[i] = ascii[asciipos];
    }        
                              
    for (int i = 0; i < length; i++){
        cout << translated[i];
    }
    cout << endl;

    return 0;
}
