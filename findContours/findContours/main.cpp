#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\topic1.jpg", 1);
	cv::Mat labelMat;//��ǩ
	cv::Mat statsMat;//״̬����
	cv::Mat centrMat;//��ͨ������
	cv::Mat hsvMat;
	cv::Mat detectMat;
	cv::Mat closeMat;//������
	cv::Mat dstMat;

	double scale = 0.1;
	Size ResImgSize = Size(srcMat.cols*scale, srcMat.rows*scale);
	cv::Mat rsrcMat = Mat(ResImgSize, srcMat.type());
	resize(srcMat, rsrcMat, ResImgSize, INTER_LINEAR);//����
	//��ɫ
	//0-180����ɫ��
	double i_minH = 0;
	double i_maxH = 10;
	//0-255���Ͷ�
	double i_minS = 43;
	double i_maxS = 255;
	//0-255����
	double i_minV = 46;
	double i_maxV = 255;
	rsrcMat.copyTo(dstMat);

	while (1)
	{
		cvtColor(rsrcMat, hsvMat, COLOR_BGR2HSV);//��ԭͼת��hsv��ʽ����Ҫ�������һλ����ΪCOLOR_BGR2HSV
		inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(18, 18));//�ṹԪ��
		morphologyEx(detectMat, closeMat, MORPH_CLOSE, kernel);//������
		//Ѱ����ͨ��
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(closeMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		//��������
		for (int i = 0; i < contours.size(); i++)
		{
			//�����С����ı���
			RotatedRect rbox = minAreaRect(contours[i]);
			cv::Size2f side = rbox.size;
			if (side.width > 10 && side.height > 10)//���
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
		cv::imshow("rsrcMat", rsrcMat);
		cv::imshow("closeMat", closeMat);
		cv::imshow("dstMat", dstMat);

		waitKey(30);
	}

	return 0;

}