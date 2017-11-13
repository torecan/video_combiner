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
IplImage* final_out;
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

void A1Divider(IplImage*imge) {


	cvSetImageROI(imge, cvRect(0, 0, a1_left[0], a1_left[1]));
	cvSetImageROI(final_out, cvRect(0, 0, a1_left[0], a1_left[1]));

	cvCopy(imge, final_out, NULL);

	cvResetImageROI(final_out);
	cvResetImageROI(imge);
	cvSetImageROI(imge, cvRect(a1_left[0], 0, a1_right[0], a1_right[1]));
	cvSetImageROI(final_out, cvRect(0, 192, a1_right[0], a1_right[1]));

	cvCopy(imge, final_out, NULL);

	cvResetImageROI(final_out);
	cvResetImageROI(img);


}



void Combiner() {

	// RIGHT IMAGE

	cvSetImageROI(capturer, cvRect(0, 0, (img1->width - 204), img1->height));
	cvSetImageROI(img1, cvRect(0, 0, (img1->width - 204), img1->height));

	cvCopy(img1, capturer, NULL);
	cvResetImageROI(img1);
	cvResetImageROI(capturer);

	// VIDEO

	cvSetImageROI(capturer, cvRect(img1->width- 204, 0, resizer->width, resizer->height));
	cvSetImageROI(resizer, cvRect(0, 0, resizer->width, resizer->height));

	cvCopy(resizer, capturer, NULL);
	cvResetImageROI(resizer);
	cvResetImageROI(capturer);

	//	LEFT IMAGE

	cvSetImageROI(capturer, cvRect((img1->width - 204 + resizer->width), 0, img2->width, img2->height));
	cvSetImageROI(img2, cvRect(0, 0, img2->width, img2->height));

	cvCopy(img2, capturer, NULL);
	cvResetImageROI(img2);
	cvResetImageROI(capturer);

}


int main(int argc, char** argv) {

	//cvNamedWindow("xample2", CV_WINDOW_AUTOSIZE);
	CvCapture* capture = cvCreateFileCapture("C://Users//t.celik//Desktop//Allianz_Familien_Eingang_04.mp4");

	img = cvQueryFrame(capture);

	img1 = cvLoadImage("C://Users//t.celik//Desktop//img1.png");
	img2 = cvLoadImage("C://Users//t.celik//Desktop//img3.png");

	final_out = cvCreateImage(cvSize(1920, 1080), img->depth, 3);

	capturer = cvCreateImage(cvSize(2976, 192), img->depth, img->nChannels);

	CvVideoWriter *writer = cvCreateVideoWriter(
		"C://Users//t.celik//Desktop//write2r.avi",
		CV_FOURCC('M', 'J', 'P', 'G'),
		20,
		cvSize(final_out->width, final_out->height));


	int r_wid = (2976  - ((img1->width -204) + img2->width));

	resizer = cvCreateImage(cvSize(r_wid, 192), img->depth, img->nChannels);
	cout << resizer->width << "\t" << img1->width << "\n" ;

	//	cout << resizer->width << resizer->height;

	while (1) {

		img = cvQueryFrame(capture);
		if (!img) break;

		cvResize(img, resizer);
		Combiner();
		A1Divider(capturer);
		//	char c = cvWaitKey(33);
		//	if (c == 27) break;
		//	cvShowImage("xample3", final_out);

		cvWriteFrame(writer, final_out);

	}

	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	cvReleaseVideoWriter(&writer);
	cvReleaseCapture(&capture);
	cvDestroyWindow("xample2");

}
