#include<opencv2/opencv.hpp>
#include"stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat image=imread("1.jpg");
	namedWindow("��ԭʼͼ��������");
	namedWindow("��Ч��ͼ��������");
	imshow("��ԭʼͼ��������",image);
	Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
	morphologyEx(image,image,MORPH_CLOSE,element);
	imshow("��Ч��ͼ��������",image);
	waitKey(0);
	return 0;
}