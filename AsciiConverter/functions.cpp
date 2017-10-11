/* FUNCTIONS USED IN ASCII CONVERTER */

// GENERATION OF GREYSCALE VALUE/ASCII CHARACTER LOOKUP TABLE
// char ascii[] - lookup table, length 256; indices = greyscale values, elements = corresponding characters
void getASCII(char ascii[]){
    char ramp[70] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*',
                        'o', 'a', 'h', 'k', 'b', 'd', 'p', 'q', 'w', 'm',
                        'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X',
                        'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't',
                        '/', '\\', '|', '(', ')', '1', '{', '}', '[', ']',
                        '?', '-', '_', '+', '~', '<', '>', 'i', 'l', '!',
                        'I', ';', ':', ',', '"', '^', '`', '\'', '.', ' '};     // Ascii chars, dark->light

    int rampval = 0;        // Index in ramp
    int greyval = 0;        // Index value representing greyscale value between 0 and 255

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
    return;
}

// TRANSLATION FROM GREYSCALE VALUES TO ASCII CHARACTERS
// int greys[] - array of greyscale values to translate to ascii chars
// char translated[] - translated version of greys
// int size - size of greys and translated
void translate(int greys[], char translated[], char ascii[], int size){
    for (int i = 0; i < size; i++){
        translated[i] = ascii[greys[i]];        // Greyscale value = index in ascii char array
    }

    return;
}
