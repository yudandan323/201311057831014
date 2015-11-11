#include<opencv/cv.h>
#include<opencv2/opencv.hpp>
#include"stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv/cxcore.h>
#include<opencv2/core/core.hpp>
#include<opencv/highgui.h>
#include<iostream>
using namespace std;
using namespace cv;  
int main(int argc,char** argv)
{
	
	IplImage* pFrame=NULL;
	CvCapture* pCapture=cvCreateCameraCapture(-1);
	cvNamedWindow("…„œÒÕ∑",1);

	while(1)
	{
		pFrame=cvQueryFrame(pCapture);
		if(!pFrame)break;
		cvShowImage("…„œÒÕ∑",pFrame);
		

		char c=cvWaitKey(33);
		if(c==27)break;

	}
	cvReleaseCapture(&pCapture);
	cvDestroyWindow("…„œÒÕ∑");
}