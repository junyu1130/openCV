#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\coin.png", 0);//��ȡͼƬֱ��ת��Ϊ�Ҷ�ͼ
	cv::Mat binaryMat;//��ֵͼ
	cv::Mat erodeMat;//��ʴͼ
	cv::Mat dilateMat;//����ͼ
	cv::Mat openMat;//������
	cv::Mat closeMat;//������

	threshold(srcMat, binaryMat, 100, 255, THRESH_BINARY);//��򷨶�ֵ��

	Mat kernel = getStructuringElement(MORPH_RECT, Size(4, 4));//�ṹԪ��
	morphologyEx(binaryMat, erodeMat, MORPH_ERODE, kernel);//��ʴ
	morphologyEx(binaryMat, dilateMat, MORPH_DILATE, kernel);//����
	morphologyEx(binaryMat, openMat, MORPH_OPEN, kernel);//������
	morphologyEx(binaryMat, closeMat, MORPH_CLOSE, kernel);//������

	imshow("��ֵͼ", binaryMat);
	imshow("��ʴ", erodeMat);
	imshow("����", dilateMat);
	imshow("������", openMat);
	imshow("������", closeMat);

	waitKey(0);

	return 0;

}


