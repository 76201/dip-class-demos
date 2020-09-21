#include <opencv.hpp>
#include "function.h"

using namespace cv;
using namespace std;


/***************************************************************************************************************************
								��6����ϰ1������canny���ӽ��б�Ե��ȡ
****************************************************************************************************************************/

void canny_extracrtion()
{

	//������ͷ
	VideoCapture cap;
	cap.open(0);

	//�ж�����ͷ�Ƿ��
	if (!cap.isOpened())
	{
		cout << "���ܴ���Ƶ�ļ�" << endl;
		return;

	}

	//��ȡ��ǰ֡��Ƭ
	Mat frame;
	cap.read(frame);


	//����ͼƬ����
	Mat dx;
	Mat dy;
	Mat canny_Mat1;
	Mat canny_Mat2;
	Mat gry_Mat;


	//ͨ��sobel���ӵõ�x��y�����ϵ��ݶ�
	/************************************************
	sobel���� ����ģ�ͣ�
	sobel( src,dx/dy,CV_16SC1,1,0,3);

	�������ܣ�
	. src��Mat�������ͼ��
	. dx/dy��x/y�����ϵ��ݶ�
	. CV_16SC1������ĸ�ʽ
	. 1��0��ʾ��x���߶�y������΢�ֵĴ���
	. 3��ʾsobel�˵Ĵ�С
	**************************************************/
	Sobel(frame, dx, CV_16S, 1, 0, 3);
	Sobel(frame, dy, CV_16S, 0, 1, 3);

	//����sobel��Ե��ȡ
	/************************************************
	Canny���� ����ģ�ͣ�
	Canny(InputArray dx, InputArray dy,
					     OutputArray edges,
				         double threshold1, double threshold2,
						 bool L2gradient = false);

	�������ܣ�
	. InputArray dx/InputArray dy������ͼ��x/y�����ϵ��ݶ�
	. dx/dy��x/y�����ϵ��ݶ�
	. OutputArray edges�������Եͼ�񣬵�ͨ����8bit��
	. double threshold1����ʾ��ֵ1
	. double threshold2����ʾ��ֵ2
	. bool L2gradient:�Ƿ���ø���ȷ�ķ�ʽ����ͼ���ݶ�
	**************************************************/
	
	Canny(dx, dy, canny_Mat1, 20, 60);
	
	//ת��Ϊ�Ҷ�ͼ���ڽ��б�Ե��ȡ
	cvtColor(frame, gry_Mat, COLOR_BGR2GRAY);

	/************************************************
	Canny���� ����ģ�ͣ�
	Canny( InputArray image, OutputArray edges,
                         double threshold1, double threshold2,
                         int apertureSize = 3, bool L2gradient = false );

	�������ܣ�
	. InputArray image������ͼ�񣬵�ͨ��8λͼ��
	. OutputArray edges�������Եͼ�񣬵�ͨ����8bit��
	. double threshold1����ʾ��ֵ1
	. double threshold2����ʾ��ֵ2
	. int apertureSize: Sobel���Ӵ�С
	. bool L2gradient: �Ƿ���ø���ȷ�ķ�ʽ����ͼ���ݶ�
	**************************************************/
	Canny(gry_Mat,canny_Mat2, 20, 60);


	imshow("canny_Mat2", canny_Mat2);
	imshow("canny_Mat1", canny_Mat1);

	waitKey(30);

}

/****************************************************************************************************************************
								��6����ϰ2��3��4 ��ת�������Լ�����任 ͶӰ�任
*****************************************************************************************************************************/

void warpaffine()
{
	//��ȡͼƬ
	cv::Mat srcMat = cv::imread("d:\\lena.jpg");

	//�ж�ͼƬ�Ƿ��ȡ�ɹ�
	if (srcMat.empty()) return;

	/**************************************************��ת������*****************************************/

	//��ʼ����ת�Ƕ��Լ����ų߶�
	auto angle{ -10.0 };
	float scale = 1;

	
	//������ת����
	cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);

	//��ñ任����
	/************************************************
	getRotationMatrix2D���� ����ģ�ͣ�
	getRotationMatrix2D( Point2f center, double angle, double scale );

	�������ܣ�
	. Point2f center��Point2f���͵�center����ʾ��ת�����ĵ�
	. double angle����ʾ��ת�ĽǶ�
	. double scale��ͼ����������

	**************************************************/
	const cv::Mat affine_matrix_zoom = cv::getRotationMatrix2D(center, angle, scale);


	//����Ž����ͼ������
	cv::Mat dstMat;

	//���÷���任����
	/************************************************
	warpAffine���� ����ģ�ͣ�
	warpAffine( InputArray src, OutputArray dst,
                              InputArray M, Size dsize,
                              int flags = INTER_LINEAR,
                              int borderMode = BORDER_CONSTANT,
                              const Scalar& borderValue = Scalar());

	�������ܣ�
	. InputArray src������ͼ��Mat����󼴿�
	. OutputArray dst�����ͼ����Ҫ��ԭͼƬ��һ���ĳߴ������
	. InputArray M��2*3�ı任����
	. Size dsize��Size���͵�dsize��ʾ���ͼ��ĳߴ�
	. int flags��int���͵�flag����ֵ�����ı�ʶ��
	. int borderMode:�߽�����ģʽ
	. const Scalar& borderValue:�㶨�߽���ȡ��ֵ

	**************************************************/
	cv::warpAffine(srcMat, dstMat, affine_matrix_zoom, srcMat.size());

	

	/**************************************************����任����*****************************************/


	Mat affine_Mat;

	//�任ǰ3������
	const cv::Point2f src_pt[] = {
		  cv::Point2f(200,200),
		  cv::Point2f(250,200),
		  cv::Point2f(200,100),
	};

	//�任��3������
	const cv::Point2f warp_pt[] = {
		  cv::Point2f(300,100),
		  cv::Point2f(300,50),
		  cv::Point2f(200,100),
	};

	//�������任��ľ���
	//��ñ任����
	/************************************************
	getAffineTransform���� ����ģ�ͣ�
	getAffineTransform( const Point2f src[], const Point2f dst[] );

	�������ܣ�
	. const Point2f src[]��ԭʼͼ��ĵ�
	. const Point2f dst[]��Ŀ��ͼ��ĵ�

	**************************************************/
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, warp_pt);

	cv::warpAffine(srcMat, affine_Mat, affine_matrix, srcMat.size());


	/**************************************************ͶӰ�任����*****************************************/
	Mat perspective_Mat;


	//�任ǰ4������
	cv::Point2f pts1[] = {
		cv::Point2f(150,150),
		cv::Point2f(150,300),
		cv::Point2f(350,300),
		cv::Point2f(350,150),

	};

	//�任��4������
	cv::Point2f pts2[] = {
	cv::Point2f(200,150),
	cv::Point2f(200,300),
	cv::Point2f(340,270),
	cv::Point2f(340,180),
	};

	//ͶӰ�任��������(3*3)
	cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	//ͶӰ�任
	/************************************************
	warpPerspective���� ����ģ�ͣ�
	warpPerspective( InputArray src, OutputArray dst,
                                   InputArray M, Size dsize,
                                   int flags = INTER_LINEAR,
                                   int borderMode = BORDER_CONSTANT,
                                   const Scalar& borderValue = Scalar());

	�������ܣ�
	. InputArray src������ͼ��Mat����󼴿�
	. OutputArray dst�����ͼ����Ҫ��ԭͼƬ��һ���ĳߴ������
	. InputArray M��͸�ӵı任����
	. Size dsize��Size���͵�dsize��ʾ���ͼ��ĳߴ�
	. int flags��int���͵�flag����ֵ�����ı�ʶ��
	. int borderMode:�߽�����ģʽ
	. const Scalar& borderValue:�㶨�߽���ȡ��ֵ

	**************************************************/
	cv::warpPerspective(srcMat, perspective_Mat, perspective_matrix, srcMat.size());


	//��ʾ���н��
	imshow("srcMat", srcMat);
	imshow("dstMat", dstMat);
	imshow("affine_Mat", affine_Mat);
	imshow("perspective_Mat", perspective_Mat);

	waitKey(0);
}


/***************************************************************************************************************************
												��6����ϰ5��ͼ�����
*****************************************************************************************************************************/
void imgcorrect()
{
	//��ȡͼƬ
	cv::Mat  src = imread("d:\\lena_rot.jpg");

	//����ͼƬ����
	cv::Mat  gry_Mat; 
	Mat correct_Mat;
	cvtColor(src,gry_Mat,COLOR_BGR2GRAY);

	//��4���㣬ͨ������任����λ��
	int height = src.rows;
	int width = src.cols;
	Point2f pst_1[4];

	//�����Ͻǵĵ�
	for (int j = 0;j < width;j++)
	{
		if (gry_Mat.at<uchar>(0, j) < 250)
		{
			pst_1[0] = Point2f(j, 0);
			j = width;
		}
	}

	//�����½ǵĵ�
	for (int j = width-1;j >0;j--)
	{
		if (gry_Mat.at<uchar>(height - 1, j) <250)
			pst_1[1] = Point2f(static_cast<float>(j), static_cast<float>(height - 1)), j = 0;
	}


	//�����½ǵĵ�
	for (int i = height-1;i >0;i--)
	{
		if (gry_Mat.at<uchar>(i, 0) <250)
			pst_1[2] = Point2f(0, static_cast<float>(i)), i = 0;
	}

	//�����Ͻǵĵ�
	for (int i = 0;i < height;i++)
	{
		if (gry_Mat.at<uchar>(i, width - 1) < 250)
			pst_1[3] = Point2f(static_cast<float>(width - 1), static_cast<float>(i)), i = height;
	}


	//�任���4����
	Point2f pst_2[4]{ Point2f(0,0),Point2f(static_cast<float>(width - 1),static_cast<float>(height - 1)),Point2f(0,static_cast<float>(height - 1)),Point2f(static_cast<float>(width - 1),0) };
	
	//����ͶӰ�任����
	const Mat Matrix = cv::getPerspectiveTransform(pst_1, pst_2);

	//����ͶӰ�任
	cv::warpPerspective(src, correct_Mat, Matrix, src.size());


	imshow("src", src);
	imshow("correct_Mat", correct_Mat);
	waitKey(0);

}

