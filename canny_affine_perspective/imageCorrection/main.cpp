#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\lena_rot.jpg", 1);//ԭͼ
	cv::Mat dstMat;
	if (srcMat.empty()) return -1;
	
	int height = srcMat.rows;
	int width = srcMat.cols;
	int x[3] = { 0 }, y[3] = { 0 };
	//��0��
	for (int j = 0; j < width; j++)
	{
		uchar average = (srcMat.at<Vec3b>(0, j)[0] +	//ĳ��ĳ��
			srcMat.at<Vec3b>(0, j)[1] +
			srcMat.at<Vec3b>(0, j)[2]) / 3;
		if (255 - average >= 15)
		{
			x[0] = j, y[0] = 0;
			break;
		}
	}
	//���һ��
	for (int i = 0; i < height; i++)
	{
		uchar average = (srcMat.at<Vec3b>(i, width - 1)[0] +
			srcMat.at<Vec3b>(i, width - 1)[1] +
			srcMat.at<Vec3b>(i, width - 1)[2]) / 3;
		if (255 - average >= 15)
		{
			x[1] = width - 1, y[1] = i;
			break;
		}
	}
	//���һ��
	for (int j = width - 1; j >= 0; j--)
	{
		uchar average = (srcMat.at<Vec3b>(height - 1, j)[0] +	
			srcMat.at<Vec3b>(height - 1, j)[1] +
			srcMat.at<Vec3b>(height - 1, j)[2]) / 3;
		if (255 - average >= 15)
		{
			x[2] = j, y[2] = height - 1;
			break;
		}
	}

	//�任ǰ����������
	const cv::Point2f src_pt[] = {
									cv::Point2f(x[0], y[0]),	//����x��y
									cv::Point2f(x[1], y[1]),
									cv::Point2f(x[2], y[2]) };
	
	//�任�����������
	const cv::Point2f dst_pt[] = {
									cv::Point2f(0, 0),
									cv::Point2f(width-1, 0),
									cv::Point2f(width-1, height-1) };

	//��÷������
	const cv::Mat affine_matrix = cv::getAffineTransform(src_pt, dst_pt);

	while (1)
	{
		cv::warpAffine(srcMat, dstMat, affine_matrix, srcMat.size());//����任����

		cv::imshow("src", srcMat);
		cv::imshow("dst", dstMat);

		waitKey(30);
	}

	return 0;

}