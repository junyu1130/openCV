#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	float histogram[256] = { 0 };//�洢ֱ��ͼ

	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\1.jpg", 0);//����0����˼�ǣ�����ȡ��ͼƬ��ȡ��ֱ��ת��Ϊ�Ҷ�ͼ��
	int height = srcMat.rows;
	int width = srcMat.cols;;
	for (int j = 0; j < height; j++)
	{
		uchar* data = srcMat.ptr<uchar>(j);//ָ��srcMat��j�е��׵�ַ
		for (int i = 0; i < width; i++)
		{
			//�õ�ֱ��ͼ
			histogram[data[i]] += 1;
		}
	}
	//�õ���һ��ֱ��ͼ
	for (int i = 0; i < 256; i++) {
		histogram[i] = histogram[i] / (height*width);
	}

	cv::Mat dispMat;
	dispMat.create(480, 512, CV_8UC3);//480�� 512��
	cv::Point pt1;//�߶����˵�
	cv::Point pt2;

	//��ֱ��ͼ
	for (int i = 0; i < 255; i++) {
		pt1.x = i * 2;
		pt1.y = 480 - histogram[i] * 480;
		pt2.x = (i + 1) * 2;
		pt2.y = 480 - histogram[i+1] * 480;
		line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);//dispMat��Բ��Ŀ��ͼ�� pt1��2�߶ε������յ� �߶ε���ɫ �߶εĴ�ϸ
															//��ӹ�ϵ��ƫ�ƣ�һ������Ĭ��ֵ��8��0
	}
	
	imshow("histogramDisp", dispMat);

	waitKey(0);

	return 0;
}