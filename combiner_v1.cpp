#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <direct.h>

using namespace cv;
using namespace std;

IplImage* img;
IplImage* img1;
IplImage* img4;


void A1Divider(IplImage*img) {

	char outname[200];

	cvSetImageROI(img, cvRect(0, 0, 300, 192));
	cvSetImageROI(img1, cvRect(300, 0, 300, 192));

	cvCopy(img, img1, NULL);

	cvResetImageROI(img1);
	cvResetImageROI(img);


}



	int main(int argc, char** argv) {
		
		cvNamedWindow("xample2", CV_WINDOW_AUTOSIZE);
		CvCapture* capture = cvCreateFileCapture("C://Users//t.celik//Desktop//video.mp4");
		IplImage* frame;
		
		frame = cvQueryFrame(capture);
		
		img = cvCreateImage(cvSize(300, 192), frame->depth, frame->nChannels);
		img1 = cvCreateImage(cvSize(900, 192), frame->depth, frame->nChannels);

		
		IplImage* frame2 = cvCreateImage(cvSize(300, 192), frame->depth, frame->nChannels);

		cout << frame->width << "  " << frame->height;
		


		while (1) {
			frame = cvQueryFrame(capture);
			cvResize(frame, frame2);
			if (!frame) break;
			cvShowImage("xample2", frame);
			A1Divider(frame2);
			cvShowImage("xample3", img1);
			char c = cvWaitKey(33);
			if (c == 27) break;
		}



		cvReleaseCapture(&capture);
		cvDestroyWindow("xample2");
	}



