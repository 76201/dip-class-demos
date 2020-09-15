#include <opencv.hpp>
#include "function.h"
using namespace cv;
using namespace std;


/***************************************************************************************************************************
												��7����ϰ1���Ľ�ͼƬ��ת
*****************************************************************************************************************************/
void spin_correct()
{
	cv::Mat srcMat = cv::imread("d:\\lena.jpg");

	//�ж�ͼƬ�Ƿ��ȡ�ɹ�
	if (srcMat.empty()) return;

	//��ʼ����ת�Ƕ��Լ����ų߶�
	auto angle{ -10.0 };
	float scale = 1;


	//������ת����
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);


	//��ñ任����																						
	Mat rot = getRotationMatrix2D(center, angle, scale);

	//��ȡ����ı���
	Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();


	//��������������
	rot.at < double >(0, 2) += bbox.width / 2.0 - center.x;
	rot.at < double >(1, 2) += bbox.height / 2.0 - center.y;


	//����Ž����ͼ������
	cv::Mat dstMat;

	//���÷���任����
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());

	cv::waitKey(0);
}


/******************************************************************************************************************************
												��7����ϰ2-3������任��ʹ��
*****************************************************************************************************************************/

/**********************************************��׼����任****************************************/
void houghDemo()
{
	Mat srcMat = cv::imread("d:\\img.png");

	//�ж�ͼ���ȡ�Ƿ�ɹ�
	if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return;
	}
	//����ͼƬ����
	Mat cannyMat;
	cv::Mat dx;
	cv::Mat dy;
	Mat lineMat;

	//canny������Ե���
	Sobel(srcMat, dy, CV_16SC1, 0, 2, 3);
	Sobel(srcMat, dx, CV_16SC1, 1, 0, 3);
	Canny(dx, dy, cannyMat, 60,180);

	//���л���任
	/************************************************
	HoughLines���� ����ģ�ͣ�
	HoughLines( InputArray image, OutputArray lines,
                              double rho, double theta, int threshold,
                              double srn = 0, double stn = 0,
                              double min_theta = 0, double max_theta = CV_PI );

	�������ܣ�
	. InputArray image��InputArray���͵�image������8bit����ͨ��
	. OutputArray lines��InputArray���͵�lines����������HoughLines�����󴢴��˻����߱任��⵽���������ʸ��
	. double rho��double���͵�rho��������Ϊ��λ�ľ��뾫��
	. double theta: double���͵�theta���Ի���Ϊ��λ�ĽǶȾ���
	. int threshold: int���͵�threshold���ۼ�ƽ�����ֵ��������ʶ��ĳ����Ϊͼ�е�һ��ֱ��ʱ�����ۼ�ƽ���б���ﵽ��ֵ
	. double srn: double���͵�srn����Ĭ��ֵ0
	. double stn: double���͵�stn����Ĭ��ֵ0�����ڶ�߶Ȼ���任��srn��ʾ���ĸ����������ߴ�ĵ�λ�Ƕ�theta�ĳ�������
	. double min_theta: double���͵� min_theta�����ڱ�׼�Ͷ�߶�Hough�任�������������С�Ƕ�
	. double max_theta: double���͵� max_theta, ���ڱ�׼�Ͷ�߶�Hough�任��������������Ƕ�

	**************************************************/
	cv::HoughLines(cannyMat, lineMat, 1, CV_PI / 180, 55);


	//ȡ��lineMat�д���ߵ���Ϣ
	int height = lineMat.rows;
	int width = lineMat.cols;

	//��ԭͼ�ϻ���
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{

			//��ȡ�Ѻ�theta
			float rho = lineMat.at<Vec3f>(i, j)[0], theta = lineMat.at<Vec3f>(i, j)[1];
			cv::Point pt1, pt2;
			double a = cos(theta);
			double b = sin(theta);
			double x0 = a*rho;
			double y0 = b*rho;


			//�������꣬saturate_cast��ֹ�������
			pt1.x = cv::saturate_cast<int>(x0 + 1000 * (-b));
			pt1.y = cv::saturate_cast<int>(y0 + 1000 * (a));
			pt2.x = cv::saturate_cast<int>(x0 - 1000 * (-b));
			pt2.y = cv::saturate_cast<int>(y0 - 1000 * (a));

			//����
			cv::line(srcMat, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
		}
	}

	imshow("srcMat", srcMat);
	cv::waitKey(0);
}

/**********************************************�ۼƸ��ʻ���任****************************************/
void houghsp_demo()
{
	Mat srcMat = cv::imread("d:\\img.png");

	//�ж�ͼ���ȡ�Ƿ�ɹ�
	if (srcMat.empty()) {
		std::cout << "failed to read image!:" << std::endl;
		return;
	}
	//����ͼƬ����
	Mat gryMat;
	Mat cannyMat;
	Mat linesp_Mat;

	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcMat, gryMat, COLOR_BGR2GRAY);
	Canny(gryMat, cannyMat, 60, 180, 3);

	//���л���任
	/************************************************
	HoughLines���� ����ģ�ͣ�
	HoughLinesP( InputArray image, OutputArray lines,
                               double rho, double theta, int threshold,
                               double minLineLength = 0, double maxLineGap = 0 );

	�������ܣ�
	. InputArray image��InputArray���͵�image������8bit����ͨ��
	. OutputArray lines��InputArray���͵�lines����������HoughLinesP�������洢�˼�⵽�����������ʸ����ÿһ�����ɾ����ĸ�Ԫ�ص�ʸ��(x_1,y_1, x_2, y_2��  ��ʾ�����У�(x_1, y_1)��(x_2, y_2) ����ÿ����⵽���߶εĽ�����
	. double rho��double���͵�rho��������Ϊ��λ�ľ��뾫��
	. double theta: double���͵�theta���Ի���Ϊ��λ�ĽǶȾ���
	. int threshold: int���͵�threshold���ۼ�ƽ�����ֵ��������ʶ��ĳ����Ϊͼ�е�һ��ֱ��ʱ�����ۼ�ƽ���б���ﵽ��ֵ
	. double minLineLength: double���͵�minLineLength����Ĭ��ֵ0����ʾ����߶εĳ��ȣ�������趨�����̵��߶ξͲ��ܱ����ֳ���
	. double maxLineGap: double���͵�maxLineGap����Ĭ��ֵ0������ͬһ�е����֮���������������ľ���

	**************************************************/
	HoughLinesP(cannyMat, linesp_Mat, 1, CV_PI / 180, 22,10 ,10);
	int heightsp = linesp_Mat.rows;
	int widthsp = linesp_Mat.cols;


	//��ԭͼ�ϻ���
	for (int i = 0;i < heightsp;i++)
	{
		for (int j = 0;j < widthsp;j++)
		{

			Point p1, p2;
			p1.x = linesp_Mat.at<Vec4i>(i, j)[0];
			p1.y = linesp_Mat.at<Vec4i>(i, j)[1];
			p2.x = linesp_Mat.at<Vec4i>(i, j)[2];
			p2.y = linesp_Mat.at<Vec4i>(i, j)[3];

			cv::line(srcMat, p1, p2, cv::Scalar(255, 255, 0), 1, 8, 0);
		}
	}

	imshow("srcMat", srcMat);
	waitKey(0);
}

