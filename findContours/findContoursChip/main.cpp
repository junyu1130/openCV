#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\chip.png", 1);
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
		threshold(grayMat, binaryMat, 150, 255, THRESH_BINARY);//��ֵ��
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
			if (fabs(1 - ratio) < 0.1 && side.width > 10 && side.height > 10)//���
			{
				//�����С����ı���
				RotatedRect rbox = minAreaRect(contours[i]);
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);
				cv::Point2f vtx[4];//�ĸ�����
				rbox.points(vtx);
				for (int j = 0; j < 4; ++j)
				{
					cv::line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
				}
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