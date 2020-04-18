// dip-class-demos.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <opencv.hpp>
#include "funtions.h"

using namespace cv;
using namespace std;

int main()
{
	int n = 20000;

	//��ʼ��ʱ
	double start = static_cast<double>(cvGetTickCount());
	
	//00.��ͨ���Գ���(trial division)Ѱ������
	pickPrime(n);

	//������ʱ
	double pp_time = ((double)cvGetTickCount() - start) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time of trial division algorithm:" << pp_time / 1000 << "ms" << endl;


	//��ʼ��ʱ
	double Estart = static_cast<double>(cvGetTickCount());

	//01.������˹����ɸ��(sieve of Eratosthenes)Ѱ������
	EratosSieve(n);
	//������ʱ
	double E_time = ((double)cvGetTickCount() - Estart) / cvGetTickFrequency();
	//��ʾʱ��
	cout << "processing time of Eratosthenes's algorithm:" << E_time / 1000 << "ms" << endl;

	//�ȴ�������Ӧ�����������������
	system("pause");
    return 0;
}

