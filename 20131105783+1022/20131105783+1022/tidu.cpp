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
	namedWindow("��ԭʼͼ����̬ѧ�ݶ�");
	namedWindow("��Ч��ͼ����̬ѧ�ݶ�");
	imshow("��ԭʼͼ����̬ѧ�ݶ�",img);
	Mat element=getStructuringElement(MORPH_RECT,Size(10,10));
	morphologyEx(img,img,MORPH_GRADIENT,element);
	imshow("��Ч��ͼ����̬ѧ�ݶ�",img);
	waitKey(0);
	return 0;
}