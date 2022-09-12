#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	float histogram[256] = { 0 };//�洢ֱ��ͼ

	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\1.jpg", 0);//����0����˼�ǣ�����ȡ��ͼƬ��ȡ��ֱ��ת��Ϊ�Ҷ�ͼ��
	int height = srcMat.rows;
	int width = srcMat.cols;
	for (int j = 0; j < height; j++)
	{
		uchar* data = srcMat.ptr<uchar>(j);//ָ��srcMat��j�е��׵�ַ
		for (int i = 0; i < width; i++)
		{
			//��ʼ��������
			histogram[data[i]] += 1;
		}
	}
	//���ֱ��ͼ
	for (int i = 0; i < 256; i++) {
		std::cout << i << ":" << histogram[i] / (height*width) << std::endl;
	}

	waitKey(0);

	return 0;
}