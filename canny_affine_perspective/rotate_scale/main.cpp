#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	while (1)
	{
		cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\lena.jpg", 1);//ԭͼ
		cv::Mat dstMat;
		if (srcMat.empty()) return -1;

		//��ת-10�㣬���ų߶�Ϊ
		float angle = -10.0, scale = 1;
		//��ת����Ϊͼ������
		cv::Point2f center(srcMat.cols*0.5, srcMat.rows*0.5);
		//��ñ任����
		const cv::Mat affine_matrix = cv::getRotationMatrix2D(center, angle, scale);

		cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());//����任����

		cv::imshow("src", srcMat);
		cv::imshow("dst", dstMat);

		waitKey(30);
	}

	return 0;

}