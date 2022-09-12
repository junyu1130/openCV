#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\rim.png", 1);
	cv::Mat grayMat;
	cv::Mat binaryMat;
	cv::Mat labelMat;//��ǩ
	cv::Mat statsMat;//״̬����
	cv::Mat centrMat;//��ͨ������
	cv::Mat dstMat;
	srcMat.copyTo(dstMat);

	while (1)
	{
		cvtColor(srcMat, grayMat, CV_RGB2GRAY);
		cv::Mat inversedMat = 255 - grayMat;//��ɫ
		threshold(inversedMat, binaryMat, 150, 255, THRESH_OTSU);//��򷨶�ֵ��
		//Ѱ����ͨ��
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(binaryMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//��������
		for (int i = 0; i < contours.size(); i++) 
		{
			//�����С����ı���
			RotatedRect rbox = minAreaRect(contours[i]);
			//�������
			cv::Size2f side = rbox.size;
			float ratio = side.width / side.height;
			if (fabs(1 - ratio)<0.05 && side.width>10 && side.height>10)//���Բ
			{
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), CV_FILLED, 8);
			}
		}
		cv::imshow("srcMat", srcMat);
		cv::imshow("grayMat", grayMat);
		cv::imshow("binaryMat", binaryMat);
		cv::imshow("dstMat", dstMat);

		waitKey(30);
	}

	return 0;

}