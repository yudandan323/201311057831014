#include"stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
Mat g_srcImage,g_dstImage;
int g_nElementShape=MORPH_RECT;//元素结构形状
//变量接受的TrackBar位置参数
int g_nMaxIterationNum=10;
int g_nOpenCloseNum=0;
int g_nErodeDilateNum=0;
int g_nTopBlackHatNum=0;
static void on_OpenClose(int,void*);
static void on_ErodeDilate(int,void*);
static void on_TopBlackHat(int,void*);
static void ShowHelpText();//帮助文字显示
int main()
{
	system("color 2F");//改变颜色
	ShowHelpText();
	g_srcImage=imread("2.jpg");
	if(!g_srcImage.data){printf("Oh,no,读取srcImg错误~！\n");return false;}
    namedWindow("【原始图】");
	imshow("【原始图】",g_srcImage);
	//创建三个产品
	namedWindow("【开运算/闭运算】",1);
    namedWindow("【腐蚀/膨胀】",1);
	namedWindow("【顶帽/黑帽】",1);
	//参数赋值
	g_nOpenCloseNum=9;
    g_nErodeDilateNum=9;
    g_nTopBlackHatNum=2;
	//创建滚动条
	createTrackbar("迭代值","【开运算/闭运算】",&g_nOpenCloseNum,g_nMaxIterationNum*2+1,on_OpenClose);
	createTrackbar("迭代值","【腐蚀/膨胀】",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("迭代值","【顶帽/黑帽】",&g_nTopBlackHatNum,g_nMaxIterationNum*2+1,on_TopBlackHat);
	//轮询获取按键信息
	while(1)
	{
		int c;//执行回调函数
		on_OpenClose(g_nOpenCloseNum,0);
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);
		//获取按键
		c=waitKey(0);
		//按下键盘按Q键或者是ESC，程序退出
		if((char)c=='q'||(char)c==27)
		break;
		//按下键盘按键1，使用椭圆（Elliptic）结构元素MORPH_ELLIPSE
		if((char)c==49)//键盘按键1的ASII码为49
		g_nElementShape=MORPH_ELLIPSE;
		//按下按键2，使用矩形（Rectangle）结构元素MORPH_RECT
		 else if((char)c==50)//键盘按键2的ASLL码为50
           g_nElementShape=MORPH_RECT;
                
		//按下按键3，使用十字形（cross-shaped）结构元素MORPH_CROSS
		else if((char)c==51)//键盘按键2的ASLL码为51
        g_nElementShape=MORPH_CROSS;
		//按下按键space，在矩形、十字形、椭圆结构元素中循环
        else if((char)c==' ')
        g_nElementShape=(g_nElementShape+1)%3;

	}
	return 0;
}
    static void on_OpenClose(int,void*)
	{
		//偏移量的定义
		int offset=g_nOpenCloseNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//偏移量的绝对值
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			morphologyEx(g_srcImage,g_dstImage,CV_MOP_OPEN,element);
		else
			morphologyEx(g_srcImage,g_dstImage,CV_MOP_CLOSE,element);

		imshow("【开运算/闭运算】",g_dstImage);

	}
	static void on_ErodeDilate(int,void*)
	{
	    int offset=g_nErodeDilateNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//偏移量的绝对值
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			erode(g_srcImage,g_dstImage,element);
		else
			dilate(g_srcImage,g_dstImage,element);
		imshow("【腐蚀/膨胀】",g_dstImage);


	}
  static void on_TopBlackHat(int,void*)
	{
		//偏移量的定义
		int offset=g_nTopBlackHatNum-g_nMaxIterationNum;
		int Absolute_offset=offset>0?offset:-offset;//偏移量的绝对值
		Mat element=getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
		if(offset<0)
			morphologyEx(g_srcImage,g_dstImage,MORPH_TOPHAT,element);
		else
			morphologyEx(g_srcImage,g_dstImage,MORPH_BLACKHAT,element);

		imshow("【顶帽/黑帽】",g_dstImage);

	}
   static void ShowHelpText()
   {
	   //输出一些帮助信息
	   printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");
	   printf("\n\n\t按键操作说明：\n\n""\t\t键盘按键【ESC】或者【Q】-退出程序\n""\t\t按键【1】-使用椭圆(Elliptic)结构元素\n""\t\t按键【2】-使用矩形(Rectangle)结构元素\n"
		   "\t\t按键【3】-使用十字形(Cross-shaped)结构元素\n""\t\t按键【space 空格】-在矩形、十字形、椭圆结构元素中循环\n""\n\n\t\t\t\t\t\t\t\t by于丹丹");
   }