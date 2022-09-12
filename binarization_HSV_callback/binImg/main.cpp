#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\1.jpg", 0);//����0����˼�ǣ�����ȡ��ͼƬ��ȡ��ֱ��ת��Ϊ�Ҷ�ͼ
	cv::Mat result1;//���ͼ ���
	cv::Mat result2;//���ͼ ��������Ӧ��ֵ��

	threshold(srcMat, result1, 100, 255, THRESH_BINARY);//���ΪTHRESH_OTSU

	adaptiveThreshold(srcMat, result2, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 15, 10);

	imshow("���", result1);
	imshow("��������Ӧ��ֵ��", result2);

	waitKey(0);

	return 0;

}


