#include "stdafx.h"
#include "cv.h"
#include "videoInput.h"
#pragma comment(linker,"/NODEFAUTLIB:atlthunk.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment( lib, "opencv_highgui220d.lib")
#pragma comment( lib, "opencv_core220d.lib")

#include "highgui.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "assert.h"
#include "math.h"
#include "float.h"
#include "limits.h"
#include "time.h"
#include "ctype.h"
#ifdef _EiC
#define WIN32
#endif

static CvMemStorage* storage=0;
static CvHaarClassifierCascade* cascade = 0;
void detect_and_draw( IplImage* image );
const char* cascade_name ="D:/OpenCV2.2/data/haarcascades/haarcascade_frontalface_alt.xml";
#define WIDTH    320
#define HEIGHT 240

int main(int argc,char** argv)
{
	IplImage *frame=cvCreateImage(cvSize(320, 240), IPL_DEPTH_8U, 3); 
	videoInput vi;//创建视频捕获对象  
    vi.setupDevice(0, WIDTH, HEIGHT);//配置设备  
    vi.showSettingsWindow(0);//该语句可以显示视频设置窗口，可以去掉 
	/*CvCapture* capture = 0;
	IplImage *frame, *frame_copy = 0;
	const char* input_name;*/
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    if( !cascade )
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
		fprintf( stderr,
        "Usage: facedetect --cascade=\"<cascade_path>\" [filename|camera_index]\n" );
        return -1;
	}
	storage = cvCreateMemStorage(0);
	/*{
		 const char* filename = (char*)"2.jpg";
		 IplImage* image = cvLoadImage( filename,1 );
		 detect_and_draw( image );
		 cvWaitKey(0);
		 cvReleaseImage( &image );
	}
	cvDestroyWindow("result");*/
	while(1)
	{
		if(vi.isFrameNew(0))
		{
			vi.getPixels(0,(unsigned char*)frame->imageData,false,true);
			if( frame )  
            {  
                detect_and_draw( frame );                         
            }  
            char c=cvWaitKey(1);  
            if(c == 27)   
                break;              //按ESC退出  
            cvNamedWindow("Video",CV_WINDOW_AUTOSIZE);  
            cvShowImage("Video",frame);  
		}
	}
	cvReleaseImage( &frame );
	return 0;
}
void detect_and_draw( IplImage* img )
{
	static CvScalar colors[] =
	{
		{{0,0,255}},
		{{0,128,255}},
		{{0,225,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,225,0}},
		{{255,0,0}},
		{{255,0,255}}
	};
	 double scale = 1.3;
	 IplImage* gray = cvCreateImage( cvSize(img->width,img->height),8,1 );
	 IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),cvRound (img->height/scale)),8, 1 );
	 int i;
	 cvCvtColor( img, gray, CV_BGR2GRAY );
     cvResize( gray, small_img, CV_INTER_LINEAR );
     cvEqualizeHist( small_img, small_img );
     cvClearMemStorage( storage );
	 if( cascade )
	 {
		 double t = (double)cvGetTickCount();
		 CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,1.1,2,0,cvSize(30, 30));
		 t = (double)cvGetTickCount() - t;
		 printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
		 for( i = 0; i < (faces ? faces->total : 0); i++ )
		 {
			 /*CvRect *r = (CvRect*)cvGetSeqElem(faces, i);
			 CvPoint pt1, pt2;
			 pt1.x = r->x*scale;
             pt2.x = (r->x+r->width)*scale;
             pt1.y = r->y*scale;
             pt2.y = (r->y+r->height)*scale;
			 cvRectangle( img, pt1, pt2, colors[i%8], 1, 8, 0 );*/
			CvRect* r = (CvRect*)cvGetSeqElem( faces, i );  
            CvPoint center;  
            int radius;  
            center.x = cvRound((r->x + r->width*0.5)*scale);  
            center.y = cvRound((r->y + r->height*0.5)*scale);  
            radius = cvRound((r->width + r->height)*0.25*scale);  
            cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );  

		 }


	 }
	 cvNamedWindow( "Video", 0);
	 cvResizeWindow( "Video",320,240);
	 cvShowImage( "Video", img );
     cvReleaseImage( &gray );
     cvReleaseImage( &small_img );
}

