#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

/***************************************************************************************************************************
                                  ������ ��ϰ1-3�� ��ֵ�˲�  ��ֵ�˲� ��˹�˲�
***************************************************************************************************************************/

void Filter()
{
	//������ͷ
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
	/************************************************
	medianBlur���� ����ģ�ͣ�
	medianBlur( InputArray src, OutputArray dst, int ksize );

	�������ܣ�
	. InputArray src��InputArray���͵�src�������Ƕ�ͨ����Mat���͵�ͼ�񣻵����ӦCV_8U��CV_16U��CV_16S��CV_32F
	. OutputArray dst��OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
	. int ksize��int���͵�ksize���׾������Գߴ磨aperture linear size����ע��������������Ǵ���1������

	**************************************************/

	medianBlur(frame, median_Mat, 3);





	//��ֵ�˲�
	/************************************************
	blur���� ����ģ�ͣ�
	blur( InputArray src, OutputArray dst,
                        Size ksize, Point anchor = Point(-1,-1),
                        int borderType = BORDER_DEFAULT );


	�������ܣ�
	. InputArray src:InputArray���͵�src�������Ƕ�ͨ����Mat���͵�ͼ�񣻵����ӦCV_8U��CV_16U��CV_16S��CV_32F
	. OutputArray dst:OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
	. Size ksize:Size���͵�ksize���ں˵Ĵ�С
	. Point anchor:Point���͵�anchor����ʾê��
	. int borderType: int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ

	**************************************************/
	blur(frame, blur_Mat, Size(3, 3), Point(-1, -1));





	//��˹�˲�
	/************************************************
	GaussianBlur���� ����ģ�ͣ�
	GaussianBlur( InputArray src, OutputArray dst, Size ksize,
                                double sigmaX, double sigmaY = 0,
                                int borderType = BORDER_DEFAULT );

	�������ܣ�
	. InputArray src��InputArray���͵�src�������Ƕ�ͨ����Mat���͵�ͼ�񣻵����ӦCV_8U��CV_16U��CV_16S��CV_32F
	. OutputArray dst��OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
	. Size ksize����˹�˴�С
	. double sigmaX, double sigmaY��X,Y�����ϵĸ�˹�˱�׼ƫ��
	. int borderType��int���͵�borderType�������ƶ�ͼ���ⲿ���ص�ĳ�ֱ߽�ģʽ

	**************************************************/
	GaussianBlur(frame, Guass_Mat, Size(3, 3), 1, 0);


	//��ʾͼƬ
	imshow("median_Mat", median_Mat);
	imshow("blur_Mat", blur_Mat);
	imshow("Guass_Mat", Guass_Mat);
	waitKey(30);
}



/***************************************************************************************************************************
										��������ϰ4������sobel���ӽ��б�Ե��ȡ
***************************************************************************************************************************/
void sobel_extracrtion()
{
	//������ͷ
	VideoCapture cap;
	cap.open(0);

	//�ж��Ƿ������ͷ
	if (!cap.isOpened())
	{
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return;
	}

	//��ȡ��ǰ֡��Ƭ
	Mat frame;
	cap.read(frame);

	//sobel��Ե���
	/************************************************
	sobel���� ����ģ�ͣ�
	Sobel( InputArray src, OutputArray dst, int ddepth,
                         int dx, int dy, int ksize = 3,
                         double scale = 1, double delta = 0,
                         int borderType = BORDER_DEFAULT );

	�������ܣ�
	. InputArray src��InputArray ���͵�src��Ϊ����ͼ����Mat���ͼ���
	. OutputArray dst��OutputArray���͵�dst����Ŀ��ͼ�񣬺����������������Ҫ��ԴͼƬ��һ���ĳߴ�����͡�
	. int ddepth��int���͵�ddepth�����ͼ������
	. int dx, int dy��X,Y�����ϵĲ�ֽ���
	. int ksize��sobel�˵Ĵ�С
	. double scale��double���͵�scale�����㵼��ֵʱ��ѡ���������ӣ�Ĭ��ֵ��1
	. double delta: double���͵�delta����ʾ�ڽ������Ŀ��ͼ���ڶ�������dst��֮ǰ��ѡ��deltaֵ����Ĭ��ֵ0
	. int borderType��int���͵�borderType���߽�ģʽ

	**************************************************/
	Mat sobel_Mat;
	Sobel(frame, sobel_Mat,-1, 1, 0, 5);

	//��ʾ���
	imshow("sobel_Mat", sobel_Mat);
	waitKey(30);
}



/***************************************************************************************************************************
										��������ϰ5����������ĥƤ����
***************************************************************************************************************************/

void Convolution_app()
{
	//������ͷ
	VideoCapture cap(0);

	//��ɫh					
	double i_minH = 0;
	double i_maxH = 20;

	//��ɫ��ɫ���Ͷ�s
	double i_minS = 43;
	double i_maxS = 255;

	//��ɫ��ɫ����v
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

		//����inRange������ͼƬ����hsvɸѡ��ѡ���������֣�
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