#include<opencv2/opencv.hpp>
#include"stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
int main()
{
	Mat image=imread("1.jpg");
	namedWindow("【原始图】闭运算");
	namedWindow("【效果图】闭运算");
	imshow("【原始图】闭运算",image);
	Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
	morphologyEx(image,image,MORPH_CLOSE,element);
	imshow("【效果图】闭运算",image);
	waitKey(0);
	return 0;
}