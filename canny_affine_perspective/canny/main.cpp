#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\lena.jpg", 0);
	Mat dstMat1;
	Mat dstMat2;
	Mat dstMatX;
	Mat dstMatY;

	while (1)
	{
		Sobel(srcMat, dstMatX, CV_16SC1, 1, 0, 3);//Sobel��Ե��ȡ x����
		Sobel(srcMat, dstMatY, CV_16SC1, 0, 1, 3);//Sobel��Ե��ȡ y����
		Canny(dstMatX, dstMatY, dstMat1, 30, 90);//Canny���ӣ�����Ϊ�ݶ���Ϣ

		Canny(srcMat, dstMat2, 30, 90, 3);//Canny���ӣ�����ΪԴͼ��

		imshow("srcMat", srcMat);
		imshow("Canny1", dstMat1);
		imshow("Canny2", dstMat2);

		waitKey(30);
	}

	return 0;

}