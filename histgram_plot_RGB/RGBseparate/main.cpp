#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	cv::Mat src_color = imread("C:\\Users\\Y\\Desktop\\ͼƬ1.png");

	std::vector<cv::Mat> channels;	//����vector����Ϊ�����3��ͨ��ͼ��ı�������
	cv::split(src_color, channels);	//����split����������src_color��rgb��ͨ��
	cv::Mat B = channels.at(0);		//����3��Mat�������3��ͨ���ķ�������
	cv::Mat G = channels.at(1);		//ע��opencv������ͨ��������˳����B, G, R
	cv::Mat R = channels.at(2);

	imshow("red", R);
	imshow("green", G);
	imshow("blue", B); //��ʾ3��ͨ����ͼ���Լ�ԭͼ
	imshow("original Mat", src_color);

	waitKey(0);

	return 0;
}

