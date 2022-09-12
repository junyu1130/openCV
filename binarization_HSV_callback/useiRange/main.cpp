#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); //��������ͷ����������ͷȡ�õ�֡��������

	double scale = 0.5;

	//0-180
	//�����ɫ
	double i_minH = 0;
	double i_maxH = 20;
	//0-255���Ͷ�
	double i_minS = 43;
	double i_maxS = 255;
	//0-255����
	double i_minV = 55;
	double i_maxV = 255;

	while (1)
	{
		Mat frame;
		Mat hsvMat;
		Mat detectMat;

		cap >> frame;
		Size ResImgSize = Size(frame.cols*scale, frame.rows*scale);
		Mat rFrame = Mat(ResImgSize, frame.type());
		resize(frame, rFrame, ResImgSize, INTER_LINEAR);//����resize

		cvtColor(rFrame, hsvMat, COLOR_BGR2HSV);//��ԭͼת��hsv��ʽ����Ҫ�������һλ����ΪCOLOR_BGR2HSV

		rFrame.copyTo(detectMat);//����һ��ԭͼ��detectMat����Ϊ��ʾ��

		//Scalar��һ���ɳ���Ϊ4������
		//	��ΪԪ�ع��ɵĽṹ�壬 Scalar
		//	�����Դ洢�ĸ�ֵ��û����
		//	����ֵĬ����0��
		cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), detectMat);

		imshow("while :in the range", detectMat);
		imshow("frame", rFrame);

		waitKey(30);
	}

	return 0;

}


