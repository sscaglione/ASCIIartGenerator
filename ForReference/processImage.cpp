#include<iostream>
#include<string>
#include<fstream>
#include<cmath>
using namespace std;

typedef unsigned char unchar; //easier to code

//useImage header file
class useImage {
	public:
		useImage(const char* fileName); //constructor
		~useImage(); //deconstructor
		void write(const char* fileName);
		void bwfilter(); //black and white filter
	private:
		ifstream* imageInFile;
		ofstream* imageOutFile;
		unchar imageHeaderData[1078] //i dont get this part ".bmp header data with offset 1078"
		unchar** imageData;
		unchar m_bwfilter[3][3]; //black and white filter
		unchar** filteredData;
};

//useImage cpp file
#ifndef _IMAGE_H
#define _IMAGE_H
#define WIDTH 128
#define HEIGHT 128

useImage::useImage(const char* fileName){

	imageData = new unchar* [HEIGHT]; // creates a new array size: height of image
	filteredData = new unchar* [HEIGHT]; // creates a new array size: height of image

	for (int i = 0; i < HEIGHT; i++)

#endif


string imageOG;
cout << "Please type the name of your image, including the file extension (i.e. jpeg, png)" << endl;
cin >> imageOG;

