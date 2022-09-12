#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); //��������ͷ

	while (1)
	{
		Mat frame;
		Mat grayMat;
		Mat dstMat;
		Mat dstMatX;
		Mat dstMatY;

		cap >> frame;

		imshow("frame", frame);
		cvtColor(frame, grayMat, COLOR_BGR2GRAY);//תΪ�Ҷ�ͼ
		imshow("Gray", grayMat);
		Sobel(grayMat, dstMat, CV_16SC1, 1, 0, 3);//Sobel��Ե��ȡ x����
		convertScaleAbs(dstMat, dstMatX);//�������ֵ���������ת����8λ
		imshow("SobelX", dstMatX);

		Sobel(grayMat, dstMat, CV_16SC1, 0, 1, 3);//Sobel��Ե��ȡ y����
		convertScaleAbs(dstMat, dstMatY);//�������ֵ���������ת����8λ
		imshow("SobelY", dstMatY);

		waitKey(30);
	}

	return 0;

}


