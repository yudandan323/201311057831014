#include"stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
Mat g_srcImage,g_dstImage;
int g_nElementShape=MORPH_RECT;//Ԫ�ؽṹ��״
//�������ܵ�TrackBarλ�ò���
int g_nMaxIterationNum=10;
int g_nOpenCloseNum=0;
int g_nErodeDilateNum=0;
int g_nTopBlackHatNum=0;
static void on_OpenClose(int,void*);
static void on_ErodeDilate(int,void*);
static void on_TopBlackHat(int,void*);
static void ShowHelpText();//����������ʾ
int main()
{
	system("color 2F");//�ı���ɫ
	ShowHelpText();
	g_srcImage=imread("2.jpg");
	if(!g_srcImage.data){printf("Oh,no,��ȡsrcImg����~��\n");return false;}
    namedWindow("��ԭʼͼ��");
	imshow("��ԭʼͼ��",g_srcImage);
	//����������Ʒ
	namedWindow("��������/�����㡿",1);
    namedWindow("����ʴ/���͡�",1);
	namedWindow("����ñ/��ñ��",1);
	//������ֵ
	g_nOpenCloseNum=9;
    g_nErodeDilateNum=9;
    g_nTopBlackHatNum=2;
	//����������
	createTrackbar("����ֵ","��������/�����㡿",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("����ֵ","����ʴ/���͡�",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("����ֵ","����ñ/��ñ��",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);
	//��ѯ��ȡ������Ϣ
	while(1)
	{
		int c;//ִ�лص�����
		on_OpenClose(g_nOpenCloseNum,0);
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);
		//��ȡ����
		c=waitKey(0);
		//���¼��̰�Q��������ESC�������˳�
		if((char)c=='q'||(char)c==27)
		break;
		//���¼��̰���1��ʹ����Բ��Elliptic���ṹԪ��MORPH_ELLIPSE
		if((char)c==49)//���̰���1��ASII��Ϊ49
		g_nElementShape=MORPH_ELLIPSE;
		//���°���2��ʹ�þ��Σ�Rectangle���ṹԪ��MORPH_RECT
		 else if((char)c==50)//���̰���2��ASLL��Ϊ50
           g_nElementShape=MORPH_RECT;
                
		//���°���3��ʹ��ʮ���Σ�cross-shaped���ṹԪ��MORPH_CROSS
		else if((char)c==51)//���̰���2��ASLL��Ϊ51
        g_nElementShape=MORPH_CROSS;
		//���°���space���ھ��Ρ�ʮ���Ρ���Բ�ṹԪ����ѭ��
        else if((char)c==' ')
        g_nElementShape=(g_nElementShape+1)%3;

	}
	return 0;
}
    static void on_OpenClose(int,void*)
	{
		//ƫ�����Ķ���
		int offset=g_nOpenCloseNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//ƫ�����ľ���ֵ
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			morphologyEx(g_srcImage,g_dstImage,CV_MOP_OPEN,element);
		else
			morphologyEx(g_srcImage,g_dstImage,CV_MOP_CLOSE,element);

		imshow("��������/�����㡿",g_dstImage);

	}
	static void on_ErodeDilate(int,void*)
	{
	    int offset=g_nErodeDilateNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//ƫ�����ľ���ֵ
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			erode(g_srcImage,g_dstImage,element);
		else
			dilate(g_srcImage,g_dstImage,element);
		imshow("����ʴ/���͡�",g_dstImage);


	}
  static void on_TopBlackHat(int,void*)
	{
		//ƫ�����Ķ���
		int offset=g_nTopBlackHatNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//ƫ�����ľ���ֵ
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			morphologyEx(g_srcImage,g_dstImage,MORPH_TOPHAT,element);
		else
			morphologyEx(g_srcImage,g_dstImage,MORPH_BLACKHAT,element);

		imshow("����ñ/��ñ��",g_dstImage);

	}
   static void ShowHelpText()
   {
	   //���һЩ������Ϣ
	   printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");
	   printf("\n\n\t��������˵����\n\n""\t\t���̰�����ESC�����ߡ�Q��-�˳�����\n""\t\t������1��-ʹ����Բ(Elliptic)�ṹԪ��\n""\t\t������2��-ʹ�þ���(Rectangle)�ṹԪ��\n"
		   "\t\t������3��-ʹ��ʮ����(Cross-shaped)�ṹԪ��\n""\t\t������space �ո�-�ھ��Ρ�ʮ���Ρ���Բ�ṹԪ����ѭ��\n""\n\n\t\t\t\t\t\t\t\t by�ڵ���");
   }