#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	VideoCapture cap;

	cap.open(0);//cap(0)��ʾ�򿪱����ĵ�һ������ͷ�� ()������Ǳ�����Ƶ��ַ��cap(��D:\\1.avi��)����Դ򿪱�����Ƶ��
	if (!cap.isOpened())//isOpened()�����Ƶ�Ƿ�����������������1
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return -1;
	}

	double fps = cap.get(CAP_PROP_FPS);//ͨ��get()����ͬ�������Ի����Ƶ�Ĳ�ͬ�������籾�������Ƶ��fps
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame; //����Mat����ͼƬ������Ϊframe����ͨ��read()�����Ƶ�ĵ�ǰ֡
		bool rSucess = cap.read(frame);
		if (!rSucess)
		{
			std::cout << "���ܴ���Ƶ�ļ��ж�ȡ֡" << std::endl;
			break;
		}
		else
		{
			cv::imshow("frame", frame); //ͨ��imshow��ʾ��ǰ֡
		}
		waitKey(30);//waitKey��ʱ30ms����ȱ�٣��޷���ʾ
	}

	return 0;
}