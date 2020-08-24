#include <opencv.hpp>
#include "function.h"

using namespace cv;
using namespace std;



//������ ��ϰ1  ͼ����̬ѧ
void morphology()
{
	//��ȡͼƬ��ת��Ϊ�Ҷ�ͼ
	Mat srcMat = imread("d:\\coin.png",0);

	//�ж϶�ȡͼƬ�Ƿ�ʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}


	//����ͼ������
	Mat thresh_Mat;
	Mat dilate_Mat;
	Mat erode_Mat;
	Mat open_Mat;
	Mat close_Mat;

	//��ֵ��
	threshold(srcMat, thresh_Mat, 100, 255, THRESH_OTSU);

	//����ṹԪ��
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	//��ʴ
	erode(thresh_Mat, erode_Mat, element, Point(-1,-1),1);

	//����
	dilate(thresh_Mat, dilate_Mat, element, Point(-1, -1), 1);

	//������
	morphologyEx(thresh_Mat, open_Mat, MORPH_OPEN, element, Point(-1, -1), 1);

	// ������
	morphologyEx(thresh_Mat, close_Mat, MORPH_CLOSE, element, Point(-1, -1), 1);


	//��ʾ���
	imshow("thresh_Mat", thresh_Mat);
	imshow("erode_Mat", erode_Mat);
	imshow("dilate_Mat", dilate_Mat);
	imshow("open_Mat", open_Mat);
	imshow("close_Mat", close_Mat);
	waitKey(0);
}

//��������ϰ2����ͨ����
void connectedwithstats()
{
	//��ȡͼƬ��ת��Ϊ�Ҷ�ͼ
	Mat srcMat = imread("d:\\coin.png");

	//�ж϶�ȡͼƬ�Ƿ�ʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//ת��Ϊ�Ҷ�ͼ
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);

	//����ͼ������
	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;

	//��򷨴���ͼ��
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);
	
	//������ͨ����
	int nComp = connectedComponentsWithStats(thresh_Mat, labels, stats, centroids, 8, CV_32S);

	//��ȥ����0�������
	cout << "Ӳ�Ҹ���Ϊ��" << nComp - 1 << endl;

	//��ʶ�������ͨ�����С��ӱ߿�
	for (int i = 1;i < nComp;i++)
	{
		Rect bandbox;
		bandbox.x = stats.at<int>(i, 0);
		bandbox.y = stats.at<int>(i, 1);

		bandbox.width = stats.at<int>(i, 2);
		bandbox.height = stats.at<int>(i, 3);

		rectangle(thresh_Mat, bandbox, 255, 1, 8, 0);
	}
	
}







//��������ϰ3 ԭ�����
void origincount()
{
	//��ȡͼƬ��ת��Ϊ�Ҷ�ͼ
	Mat srcMat = imread("d:\\1.jpg");

	//�ж϶�ȡͼƬ�Ƿ�ʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//ת��Ϊ�Ҷ�ͼ
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);



	//��ɫ
	gryMat = 255 - gryMat;

	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;
	Mat erode_Mat;

	//��򷨴���ͼ��
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);


	//����ṹԪ��
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));

	//��ͼ����и�ʴ������������
	erode(thresh_Mat, erode_Mat, element, Point(-1, -1), 2);



	//������ͨ����
	int nComp = connectedComponentsWithStats(erode_Mat, labels, stats, centroids, 8, CV_32S);

	//��ȥ����0�������
	cout << "ԭ�����Ϊ��" << nComp - 1 << endl;

}




//��������ϰ4 ���������
void clipcount()
{
	//��ȡͼƬ��ת��Ϊ�Ҷ�ͼ
	Mat srcMat = imread("d:\\clip.png");

	//�ж϶�ȡͼƬ�Ƿ�ʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//ת��Ϊ�Ҷ�ͼ
	Mat gryMat;
	cvtColor(srcMat, gryMat, COLOR_BGRA2GRAY);

	//��ɫ
	gryMat = 255 - gryMat;

	Mat stats;
	Mat centroids;
	Mat labels;
	Mat thresh_Mat;
	Mat open_Mat;

	//��򷨴���ͼ��
	threshold(gryMat, thresh_Mat, 100, 255, THRESH_OTSU);


	//����ṹԪ��
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));

	//��ͼ����п����㴦������һЩ�ӵ�
	morphologyEx(thresh_Mat, open_Mat, MORPH_OPEN, element, Point(-1, -1), 1);



	//������ͨ����
	int nComp = connectedComponentsWithStats(open_Mat, labels, stats, centroids, 8, CV_32S);


	//�Ƚϳ���ȣ�ɸѡ��������ͨ��
	for (int i = 1;i < nComp;i++)
	{
		int width = stats.at<int>(i, 2);
		int height = stats.at<int>(i, 3);
		int ratio =  height/ width;
		if (ratio > 10)
		{
			nComp--;
		}
	}

	//��ȥ����0�������
	cout << "���������Ϊ��" << nComp - 1 << endl;
	
}