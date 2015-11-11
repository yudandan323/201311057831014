#include<opencv2/opencv.hpp>
#include"stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"stdafx.h"
using namespace std;
using namespace cv;
int main()
{
	Mat img=imread("1.jpg");
	namedWindow("【原始图】形态学梯度");
	namedWindow("【效果图】形态学梯度");
	imshow("【原始图】形态学梯度",img);
	Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
	morphologyEx(img,img,MORPH_GRADIENT,element);
	imshow("【效果图】形态学梯度",img);
	waitKey(0);
	return 0;
}