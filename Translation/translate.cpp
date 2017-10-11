/* Amy Byrnes; 4/18/17; CSE 20312 - Data Structures
 * translate.cpp
 * Translate an array of interger values to ascii characters using lookup table
 */

#include <iostream>
using namespace std;

// int greys[] - array of greyscale values to translate to ascii chars
// char translated[] - translated version of greys
// int size - size of greys and translated
void translate(int greys[], char translated[], int size){
    // CREATE LOOKUP TABLE OF ASCII VALUES -> move this into main execution or its own function?
    char ramp[70] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*',
                        'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm',
                        'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
                        'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't',
                        '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',
                        '?', '-', '_', '+', '~', '<', '>', 'i', 'l', '!',
                        'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '};     // Ascii chars, dark->light

    char ascii[256];
    int rampval = 0;
    int greyval = 0;

    while (greyval < 255){      // 255 possible greyscale values are represented by 70 ascii chars
        if (greyval < 184){     // Assign 46 characters to greyscale values 0 - 183; 4 vals to every 1 ramp char
            for (int i = 0; i < 4; i++){
                ascii[greyval] = ramp[rampval];
                greyval++;
            }
        }
        else{       // Assign remaining 24 characters to greyscale values 184 - 255; 3 vals to every 1 ramp char
            for (int i = 0; i < 3; i++){
                ascii[greyval] = ramp[rampval];
                greyval++;
            }
        }
        rampval++;
    }

    // TRANSLATE GREYSCALE VALUES TO ASCII CHARACTERS
    for (int i = 0; i < size; i++){
        translated[i] = ascii[greys[i]];        // Greyscale value = index in ascii char array
    }

    return;
}


// TEST OF TRANSLATE FUNCTION
int main(){
    int size = 10;
    /*int size = 256;
    int greys[size];        // Array of greyscale values
    for (int i = 0; i < size; i++){
        greys[i] = i;
    }*/
    char translated[size];      // Array of greyscale values translated into ascii characters
    int greys[size] = {9, 10, 20, 30, 40, 50, 200, 222, 119, 78};       // Greyscale values

    cout << "BEFORE:" << endl;
    for (int i = 0; i < size; i++){
        cout << greys[i] << " ";
    }
    cout << endl;

    translate(greys, translated, size);

    cout << "AFTER:" << endl;
    for (int i = 0; i < size; i++){
        cout << i << ": " << translated[i] << endl;
    }
    cout << "END" << endl;

    return 0;
}
