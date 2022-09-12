#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); //��������ͷ

	//0-180
	//�����ɫ
	double i_minH = 0;
	double i_maxH = 20;
	//0-255���Ͷ�
	double i_minS = 43;
	double i_maxS = 255;
	//0-255����
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;
		Mat medMat;
		Mat dstMat;

		cap >> frame;

		cvtColor(frame, hsvMat, COLOR_BGR2HSV);//��ԭͼת��hsv��ʽ����Ҫ�������һλ����ΪCOLOR_BGR2HSV

		frame.copyTo(detectMat);//����һ��ԭͼ��detectMat����Ϊ��ʾ��
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		GaussianBlur(frame, medMat, Size(5, 5), 3, 3);//��˹�˲�

		frame.copyTo(dstMat);
		medMat.copyTo(dstMat, detectMat);

		imshow("frame", frame);
		imshow("while :in the range", detectMat);
		imshow("GaussianFilter", dstMat);

		waitKey(30);
	}

	return 0;

}


