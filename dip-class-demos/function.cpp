
#include<iostream>
#include<opencv2/opencv.hpp>
#include"function.h"
using namespace cv;
using std::cout;
using std::endl;

/*****************************************************************************************************************************
										��������ϰ1����ɫ��ȡʵ��
								���ò�ͬɫ��������HSVɫ�ʿռ��ϵĲ�ͬɫ��ʵ�ֶ��˷�ɫ����ȡ
*****************************************************************************************************************************/
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

			/************************************************
			cvTColor ����ģ�ͣ�
			cvtColor( InputArray src, OutputArray dst, int code, int dstCn = 0 );

			�������ܣ�
			. InputArray src: ����ͼ��Ҫ������ɫ�ռ�任��ԭͼ�񣬿�����Mat��
			. OutputArray dst: ���ͼ�񼴽�����ɫ�ռ�任��洢ͼ��Ҳ����Mat��
			. int code: ת���Ĵ�����ʶ�����ڴ�ȷ����ʲô��ʽ��ͼƬת����ʲô��ʽ��ͼƬ��
			. int dstCn = 0: Ŀ��ͼ��ͨ���������ȡֵΪ0������src��code����
			
			**************************************************/
			cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);

			//��detecMat���г�ʼ��
			frame.copyTo(detectMat);
			//����inRange������ͼƬ����hsvɸѡ

			/************************************************
			inRange ����ģ�ͣ�
			inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)��

			�������ܣ�
			. InputArray src: ����Ҫ�����ͼ�񣬿���Ϊ��ͨ�����ͨ��
			. InputArray lowerb: �����±߽����������
			. InputArray upperb: �����ϱ߽���������
			. OutputArray dst: ���ͼ��������ͼ��src �ߴ���ͬ��ΪCV_8U ����

			**************************************************/
			cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);


			imshow("while:in the range", detectMat);
			imshow("frame", rFrame);

			waitKey(30);
		}
	
}

/*****************************************************************************************************************************
														��������ϰ2��
													���ü���ͼ���ֵ���ķ���
*****************************************************************************************************************************/
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

	/************************************************
	threshold ����ģ�ͣ�
	threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)��

	�������ܣ�
	. InputArray src: ����Ҫ�����ͼ�񣬿���Ϊ��ͨ�����ͨ��
	. OutputArray dst: ���ͼ��������ͼ��src �ߴ���ͬ��ΪCV_8U ����
	. double thresh:��ֵ
	. double maxval:���ͼ�����ֵ
	. int type:��ֵ����
			0: THRESH_BINARY  ��ǰ��ֵ������ֵʱ��ȡMaxval,��������Ϊ0
			1: THRESH_BINARY_INV ��ǰ��ֵ������ֵʱ������Ϊ0����������ΪMaxval
			2: THRESH_TRUNC ��ǰ��ֵ������ֵʱ������Ϊ��ֵ�����򲻸ı�
			3: THRESH_TOZERO ��ǰ��ֵ������ֵʱ�����ı䣬��������Ϊ0
			4: THRESH_TOZERO_INV  ��ǰ��ֵ������ֵʱ������Ϊ0�����򲻸ı�
			...
			8:THRESH_OTSU  ͨ�������������ֵ��������ֵ��255��С����0
	

	**************************************************/

	//��ͨ��ֵ������
	threshold(srcMat, bin_Mat, 100, 255, CV_THRESH_BINARY);

	//���
	threshold(srcMat, otsu_Mat, 100, 255, CV_THRESH_OTSU);

	/************************************************
	adaptiveThreshold ����ģ�ͣ�
	adaptiveThreshold( InputArray src, OutputArray dst,double maxValue, int adaptiveMethod,int thresholdType, int blockSize, double C );

	�������ܣ�
	. ����1��InputArray���͵�src������ͼ���ͨ������8λ��������Mat���ɡ�
	. ����2�����������Ľ��������⡣��Ϊ���ͼ��������ͼ��ͬ���ĳߴ�����ͣ���
	. ����3��Ԥ���������������ֵ��
	. ����4��ָ������Ӧ��ֵ�㷨����ѡ��ADAPTIVE_THRESH_MEAN_C �� ADAPTIVE_THRESH_GAUSSIAN_C���֡�
	. ����5��ָ����ֵ���͡���ѡ��THRESH_BINARY����THRESH_BINARY_INV���֡�������������ֵ�򷴶�������ֵ����
	. ����6����ʾ������С����������������ֵ��һ��ѡ��Ϊ3��5��7......�ȡ�
    . ����7������C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ�����

	**************************************************/
	//��������Ӧ��ֵ��
	adaptiveThreshold(srcMat, adap_Mat, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 10);//�ʺ϶���Щ���ղ�����ͼƬ���ж�ֵ������Ϊ���Ķ�ֵ����ֵ������Ӧ��

	//��ʾ���ͼ��
	cv::imshow("bin_Mat", bin_Mat);
	cv::imshow("otsu_Mat", otsu_Mat);
	cv::imshow("adap_Mat", adap_Mat);
	

	cv::waitKey(0);
}

/*****************************************************************************************************************************
														��������ϰ3��
										����һ������������ͨ���ƶ����������ڶ�ֵ����ֵ
******************************************************************************************************************************/


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

	/************************************************
	createTrackbar���� ����ģ�ͣ�
	createTrackbar(const String& trackbarname, const String& winname,
                              int* value, int count,
                              TrackbarCallback onChange = 0,
                              void* userdata = 0);

	�������ܣ�
	. ����1��const String&���͵�trackbarname����������켣��������
	. ����2��onst String&���͵�winname,�����ռ�����������ͼ�񴰿ڵ����ơ�
	. ����3��int* ���͵�value����ʼ����ֵ��
	. ����4��int����count�������ռ�Ŀ̶ȷ�Χ��
	. ����5�� TrackbarCallback���͵�onChange������һ��ָ��ص�������ָ�롣
	. ����6��void* ���͵�userdata���û������ص����������ݣ���������켣���¼���

	**************************************************/
	//��������������
	createTrackbar("threshold", "bar", &lowth, maxth, callback, &gryMat);
	cv::waitKey(0);

}

