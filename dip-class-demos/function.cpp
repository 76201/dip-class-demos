
#include<iostream>
#include<opencv2/opencv.hpp>
#include"function.h"
using namespace cv;
using std::cout;
using std::endl;

/**********************************
��������ϰ1����ɫ��ȡʵ��
���ò�ͬɫ��������HSVɫ�ʿռ��ϵĲ�ͬɫ��ʵ�ֶ��˷�ɫ����ȡ
************************************/
void skinRecognition()
{
		VideoCapture cap(0);//��0������ͷ
		double scale = 0.5;

		//��ɫh					
		double i_minH = 0;
		double i_maxH = 20;

		//��ɫ���Ͷ�s
		double i_minS = 43;
		double i_maxS = 255;

		//��ɫ����v
		double i_minV = 55;
		double i_maxV = 255;

		while (1)
		{
			//����ͼ������
			Mat frame;
			Mat hsvMat;
			Mat detectMat;

			cap >> frame;//��ȡ��ǰ֡����Ƭ

			//�޸�ͼƬ�ߴ��С
			Size ResImgSiz = Size(frame.cols*scale, frame.rows*scale);
			Mat rFrame = Mat(ResImgSiz, frame.type());
			resize(frame, rFrame, ResImgSiz, INTER_LINEAR);

			//��ԭͼת��Ϊhsv���͵�ͼƬ
			cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

			//��detecMat���г�ʼ��
			frame.copyTo(detectMat);
			//����inRange������ͼƬ����hsvɸѡ
			cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);


			imshow("while:in the range", detectMat);
			imshow("frame", rFrame);

			waitKey(30);
		}
	
}

/**********************************
��������ϰ2��
���ü���ͼ���ֵ���ķ���
************************************/
void binarization()
{
	//��ȡͼƬ��ת��Ϊ�Ҷ�ͼ
	cv::Mat srcMat = cv::imread("d:\\timg.jpg", 0);

	//�ж�ͼƬ�Ƿ���ȡ�ɹ�
	if (srcMat.empty())
	{
		cout << "fail to read !" << endl;
		return;
	}


    //����ͼ������
	cv::Mat bin_Mat;
	cv::Mat otsu_Mat;
	cv::Mat adap_Mat;


	//��ͨ��ֵ������
	threshold(srcMat, bin_Mat, 100, 255, CV_THRESH_BINARY);

	//���
	threshold(srcMat, otsu_Mat, 100, 255, CV_THRESH_OTSU);

	//��������Ӧ��ֵ��
	adaptiveThreshold(srcMat, adap_Mat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);//�ʺ϶���Щ���ղ�����ͼƬ���ж�ֵ������Ϊ���Ķ�ֵ����ֵ������Ӧ��

	//��ʾ���ͼ��
	cv::imshow("bin_Mat", bin_Mat);
	cv::imshow("otsu_Mat", otsu_Mat);
	cv::imshow("adap_Mat", adap_Mat);
	

	cv::waitKey(0);
}

/**********************************
��������ϰ3��
����һ������������ͨ���ƶ����������ڶ�ֵ����ֵ
************************************/


//�ص�����
void callback(int th, void* data)
{
	//ǿ������ת��
	cv::Mat src = *((cv::Mat*) data);

	//�������ͼƬ����
	cv::Mat dst;

	//��ֵ������
	threshold(src, dst, th, 255, CV_THRESH_BINARY);
	cv::imshow("bar", dst);
}
//������
void trackbar()
{	
	//����ͼ������
	cv::Mat srcMat;
	cv::Mat gryMat;


	//��ʼ����������ֵ�������û����ڵĵ��ڷ�Χ
	int lowth = 30;
	int maxth = 255;
	
	//��ȡͼƬ
	srcMat = cv::imread("d:\\timg.jpg");

	//�ж�ͼƬ��ȡ�Ƿ�ɹ�
	if (srcMat.empty())
	{
		cout << "fail to read!" << endl;
	}

	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);

	//��ʾ�Ҷ�ͼ
	namedWindow("bar");
	cv::imshow("bar", gryMat);

	//��������������
	createTrackbar("threshold", "bar", &lowth, maxth, callback, &gryMat);
	cv::waitKey(0);

}

