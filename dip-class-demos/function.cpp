#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

//������ ��ϰ1��3 ��ֵ�˲�  ��ֵ�˲� ��˹�˲�
void Filter()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return;

	}

	//��ȡ��ǰ֡��Ƭ
	Mat frame;
	cap.read(frame);


	//����ͼ������
	Mat median_Mat;
	Mat blur_Mat;
	Mat Guass_Mat;

	//��ֵ�˲�
	medianBlur(frame, median_Mat, 3);

	//��ֵ�˲�
	blur(frame, blur_Mat, Size(3, 3), Point(-1, -1));

	//��˹�˲�
	GaussianBlur(frame, Guass_Mat, Size(3, 3), 1, 0);


	//��ʾͼƬ
	imshow("median_Mat", median_Mat);
	imshow("blur_Mat", blur_Mat);
	imshow("Guass_Mat", Guass_Mat);
	waitKey(30);
}

//��������ϰ4 ��Ե��ȡ
void sobel_extracrtion()
{
	VideoCapture cap;
	cap.open(0);
	if (!cap.isOpened())
	{
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return;

	}

	//��ȡ��ǰ֡��Ƭ
	Mat frame;
	cap.read(frame);

	//sobel��Ե���
	Mat sobel_Mat;
	Sobel(frame, sobel_Mat,-1, 1, 0, 5);
	imshow("sobel_Mat", sobel_Mat);
	waitKey(30);
}

//��������ϰ5 ĥƤ����
void Convolution_app()
{
	//�����ܷ�ɫ��ȡ����
	VideoCapture cap(0);//��0������ͷ

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
		Mat maskMat;
		Mat objectMat;
		Mat guss_Mat;


		cap >> frame;//��ȡ��ǰ֡����Ƭ

		//��ԭͼת��Ϊhsv���͵�ͼƬ
		cvtColor(frame, hsvMat, COLOR_BGR2HSV);

		//��detecMat���г�ʼ��
		frame.copyTo(maskMat);


		//����inRange������ͼƬ����hsvɸѡ
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), maskMat);

		//ԭͼ���������
		frame.copyTo(objectMat);

		//��ͼ����и�˹�˲�
		GaussianBlur(frame, guss_Mat, Size(5, 5), 3, 0);

		//��˹�˲����������������Ŀ��ͼ��
		guss_Mat.copyTo(objectMat, maskMat);//��ԭͼ��ȡ��Ŀ��ͼ�������㣩


		//��ʾ���
		imshow("ĥƤǰ", frame);
		imshow("ĥƤ��", objectMat);
	
		waitKey(30);
	}
		
}