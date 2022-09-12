#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\lena.jpg", 1);//ԭͼ
	cv::Mat dstMat;
	if (srcMat.empty()) return -1;

	//�任ǰ���ĵ�����
	const cv::Point2f pts1[] = {
									cv::Point2f(150, 150),
									cv::Point2f(150, 300),
									cv::Point2f(350, 300),
									cv::Point2f(350, 150) };
	//�任����ĵ�����
	const cv::Point2f pts2[] = {
									cv::Point2f(250, 150),
									cv::Point2f(200, 300),
									cv::Point2f(340, 270),
									cv::Point2f(340, 180) };
	//���͸�Ӿ���
	const cv::Mat perspective_matrix = cv::getPerspectiveTransform(pts1, pts2);

	while (1)
	{
		cv::warpPerspective(srcMat, dstMat, perspective_matrix, srcMat.size());//͸�ӱ任����

		cv::imshow("src", srcMat);
		cv::imshow("dst", dstMat);

		waitKey(30);
	}

	return 0;

}