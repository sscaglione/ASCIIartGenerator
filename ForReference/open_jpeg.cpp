#include <stdio.h>
#include <iostream>
#include "highgui.h"
#include "opencv.h"
//Melissa Pech
int main() {
//storing the color image in object 
	IplImage* img = cvLoadImage("photo.jpg");
//
////Now convert the image to grayscale using inbuilt function
	IplImage* grayimg = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, grayimg, CV_RGB2GRAY);
//
////This will create a window for color image
	cvNamedWindow("Window1", CV_WINDOW_AUTOSIZE);
//
////This will create a window for grayscale image
	cvNamedWindow("Window2", CV_WINDOW_AUTOSIZE);
//
////Display the colour image
	cvShowImage("Window1", img);
//
//// Display grayscale image
	cvShowImage("Window2", grayimg);
//
////Show it for n number of seconds
	cvWaitKey(2000);
//
	cvReleaseImage(&img);
//
	cvDestroyWindow("Window1");
//
	cvReleaseImage(&grayimg);
//
	cvDestroyWindow("Window2");
//
return 0;
//
}
