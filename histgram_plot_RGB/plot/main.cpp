#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	cv::Mat dispMat;
	dispMat.create(240, 240, CV_8UC3);////����240��240�У�������8λunsigned char 3ͨ��
	cv::Point pt;//Opencv�ж���һ�������䣬Ȼ���x, y������ֵ��ֵ
	cv::Point pt1;//�߶����˵�
	cv::Point pt2;
	//��Բ
	pt.x = 50;
	pt.y = 50;
	circle(dispMat, pt, 10, CV_RGB(255, 0, 0), 1, 8, 0);//dispMat��Բ��Ŀ��ͼ�� ptԲ�ĵĵ� Բ�İ뾶 Բ����ɫ
														//Բ��������ϸ��ȡ-1Ϊ����ʵ��Բ ��ӹ�ϵ��ƫ�ƣ�һ������Ĭ��ֵ��8��0
	//���߶�
	pt1.x = 100;
	pt1.y = 100;
	pt2.x = 150;
	pt2.y = 150;
	line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);//dispMat��Բ��Ŀ��ͼ�� pt1��2�߶ε������յ� �߶ε���ɫ �߶εĴ�ϸ
														//��ӹ�ϵ��ƫ�ƣ�һ������Ĭ��ֵ��8��0
	//������
	cv::Rect rect;
	rect.x = 200;
	rect.y = 200;
	rect.width = 10;
	rect.height = 10;
	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);//dispMat�����ε�Ŀ��ͼ�� �����Ƶľ��� ���ε���ɫ 
															//���εĴ�ϸ�� -1��Ϊʵ�ľ��� ��ӹ�ϵ��ƫ�ƣ�һ������Ĭ��ֵ8��0

	imshow("plot", dispMat);

	waitKey(0);

	return 0;
}