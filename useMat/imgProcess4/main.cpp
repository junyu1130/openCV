#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	uchar threshold = 100;//��ֵ

	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\1.jpg");
	cv::Mat deepMat;
	cv::Mat shallowMat;
	srcMat.copyTo(deepMat);//��ƣ�������������
	shallowMat = srcMat;//ǳ���ƣ�ָ��ԭ����

	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			//��ʼ��������
			uchar average = (srcMat.at<Vec3b>(j, i)[0] +
				srcMat.at<Vec3b>(j, i)[1] +
				srcMat.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold) average = 255;//��ֵ������
			else average = 0;
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}

	imshow("src", srcMat);
	imshow("deep", deepMat);
	imshow("shallow", shallowMat);

	waitKey(0);

	return 0;
}