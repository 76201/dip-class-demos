#include<iostream>
#include<opencv2/opencv.hpp>
#include"function.h"

using namespace cv;
using namespace std;

int main()
{
	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());

	//������
	//skinRecognition();
	//binarization();
	trackbar();

	//������ʱ
	double time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time:" << time / 1000 << "ms" << endl;

	cin.get();
	return 0;
}
