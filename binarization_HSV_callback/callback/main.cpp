#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//Trackbar�Ļص�����
void threshod_Mat(int th, void* data)
{
	Mat src = *(Mat*)(data);

	Mat dst;
	//��ֵ��
	threshold(src, dst, th, 255, 0);

	imshow("binaryMat", dst);
}

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\1.jpg", 0);//����0����˼�ǣ�����ȡ��ͼƬ��ȡ��ֱ��ת��Ϊ�Ҷ�ͼ

	int lowTh = 30;
	int maxTh = 255;

	imshow("binaryMat", srcMat);
	createTrackbar("threshold",
					"binaryMat",
					&lowTh,
					maxTh,
					threshod_Mat,
					&srcMat);

	waitKey(0);

	return 0;

}


