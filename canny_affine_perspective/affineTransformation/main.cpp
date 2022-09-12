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

		//�任ǰ����������
		const cv::Point2f src_pt[] = {
										cv::Point2f(200, 200),
										cv::Point2f(250, 200),
										cv::Point2f(200, 100) };
		//�任�����������
		const cv::Point2f dst_pt[] = {
										cv::Point2f(300, 100),
										cv::Point2f(300, 50),
										cv::Point2f(200, 100) };
		//��÷������
		const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

		cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());//����任����

		cv::imshow("src", srcMat);
		cv::imshow("dst", dstMat);

		waitKey(30);
	}

	return 0;

}