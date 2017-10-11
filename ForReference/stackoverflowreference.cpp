

#ifndef _IMAGE_H
#define _IMAGE_H

#define WIDTH 128
#define HEIGHT 128

#include <iostream>
#include <cmath>
#include <fstream> // for file I/O

using namespace std;

#endif

using namespace std;
typedef unsigned char unchar; //basically this is just so we don't have to type unsigned char every time

// image.h

class inputImage {

public:
    inputImage(const char* fileName); //Constructor
    ~inputImage(); //Deconstructor
    void write(const char* fileName);
    //void grayscaleFilter(); //grayscale filer.
private:
    ifstream* picInFile; 
    ofstream* picOutFile;
    unchar imageHeaderData[1078]; //.bmp header data with offset 1078.
    unchar** imageData;
    //unchar m_grayscaleFilter[3][3]; // Grayscale Filter.
    unchar**  filteredData;
};

//  image.cpp
//

//Constructor

inputImage::inputImage(const char* fileName){

    imageData = new unchar* [HEIGHT]; // create new array size: height of image.
    filteredData = new unchar* [HEIGHT];// create new array size: height of image.

    for (int i = 0; i < HEIGHT; i++) {

        imageData[i] = new unchar [WIDTH]; //create matrix.
        filteredData[i] = new unchar [WIDTH]; //create matrix.
    }

    //image I/O
    picInFile = new ifstream;
    picInFile->open(fileName, ios::in | ios::binary); // open fileName and read as binary.
    picInFile->seekg(0, ios::beg); //pos filter at beginning of image file.
    picInFile->read(reinterpret_cast<char*>(imageHeaderData),1078); //read bmp header data into array.

    for(int i=0; i<HEIGHT; i++) {
        picInFile->read(reinterpret_cast<char*>(imageData[i]),WIDTH);//read row into each array entry.
    }

    picInFile->close(); //close stream.

}

inputImage::~inputImage(){

    delete picInFile;
    delete picOutFile;

    for(int i=0; i<HEIGHT; i++){
        delete[] imageData[i];
        delete[] filteredData[i];
    }

    delete[] imageData;
    delete[] filteredData;
}

void inputImage::write(const char* fileName) {

    grayscaleFilter();
    picOutFile = new ofstream;
    picOutFile->open(fileName, ios::out | ios::trunc | ios::binary);
    picOutFile->write(reinterpret_cast<char*>(imageHeaderData), 1078); //write header data onto output

    for(int i = 0; i < HEIGHT; i++){

        picOutFile->write(reinterpret_cast<char*>(filteredData[i]),WIDTH); // write new image data.

    }

    picOutFile->close(); //close stream
}

//void inputImage::grayscaleFilter(){
//}

//  Main.cpp
//

using namespace std;

int main() {

    inputImage img("test.bmp");
    img.write("output.bmp");
    return 0;

}