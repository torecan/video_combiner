/*
STUDIO VISION IMAGE/VIDEO/IMAGE FOR SOUTH AND NORTH SCREENS
MÜNCHEN 2017
TÖRECAN CELIK
*/

#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <direct.h>

using namespace cv;
using namespace std;

IplImage* capturer;
IplImage* img;
IplImage* img1;
IplImage* img2;
IplImage* resizer;

char orginalname[200];
char filename[200];
char fullname[200];
char dirname[200];
char ext[1];


int a1_right[2] = { 1440,192 };
int a1_left[2] = { 1536,192 };

int a4_right[2] = { 1184,192 };
int a4_left[2] = { 1152,192 };

int nord_right[2] = { 1184,192 };


int width, height;




void Combiner() {
	

	cvSetImageROI(capturer, cvRect(0, 0, img1->width, img1->height));
	cvSetImageROI(img1, cvRect(0, 0, img1->width, img1->height));
	
	cvCopy(img1, capturer, NULL);
	cvResetImageROI(img1);
	cvResetImageROI(capturer);

	// 

	cvSetImageROI(capturer, cvRect(img1->width, 0, resizer->width , resizer->height));
	cvSetImageROI(resizer, cvRect(0, 0, resizer->width, resizer->height));

	cvCopy(resizer,capturer, NULL);
	cvResetImageROI(resizer);
	cvResetImageROI(capturer);
	
}


int main(int argc, char** argv) {

	//cvNamedWindow("xample2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("C://Users//t.celik//Desktop//video.mp4");
		
	img = cvQueryFrame(capture);
	
	img1 = cvLoadImage("C://Users//t.celik//Desktop//right.jpg");
	img2 = cvLoadImage("C://Users//t.celik//Desktop//left.jpg");
	
	
	capturer= cvCreateImage(cvSize(5000, 192), img->depth, img->nChannels);
	

	int r_wid = (2336 - 5 -(img1->width + img2->width));
	
	resizer = cvCreateImage(cvSize(r_wid, 192), img->depth, img->nChannels);

	cout << resizer->width << resizer->height;

	while (1) {

		img = cvQueryFrame(capture);
		cvResize(img,resizer);
	
		//cvShowImage("xample2", img);
		Combiner();
		cvShowImage("xample3", capturer);

		char c = cvWaitKey(33);
		if (c == 27) break;
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("xample2");

}


