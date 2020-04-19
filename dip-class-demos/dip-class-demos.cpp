// dip-class-demos.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	//Ѱ��2-n��Χ�ڵ�����
	int n = 50000000;
	//�Ƿ��ҵ���������ӡ��״̬��
	bool ifPrint = false;

	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());
	
	//00.��ͨ���Գ���(trial division)Ѱ������
	pickPrime(n, ifPrint);

	//������ʱ
	double pp_time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time of trial division algorithm:" << pp_time / 1000 << "ms" << endl;


	//��ʼ��ʱ
	double Estart = static_cast<double>(cvGetTickCount());
	//01.������˹����ɸ��(sieve of Eratosthenes)Ѱ������
	EratosSieve(n,ifPrint);
	//������ʱ
	double E_time = ((double)cvGetTickCount() - Estart) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time of Eratosthenes's algorithm:" << E_time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
    return 0;
}

