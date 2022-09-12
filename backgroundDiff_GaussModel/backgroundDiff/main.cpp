#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int sub_threshold = 0;
Mat bgMat;
Mat subMat;
Mat bny_subMat;

void threshold_track(int, void *)//������Ƕ����һ���ص�������������canny��صĲ���
{

	threshold(subMat, bny_subMat, sub_threshold, 255, CV_THRESH_BINARY);
	imshow("Result", bny_subMat);
}

int bgSub_demo()
{
	VideoCapture capVideo(0); //��������ͷ

	//�����Ƶ��ʧ��
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	int cnt = 0;

	Mat frame;

	while (1)
	{
		capVideo >> frame;
		cvtColor(frame, frame, COLOR_BGR2GRAY);

		if (cnt == 0) {
			//��һ֡����ñ���ͼ��
			frame.copyTo(bgMat);
		}
		else {
			//�ڶ�֡��ʼ�������
			//����ͼ��͵�ǰͼ�����
			absdiff(frame, bgMat, subMat);
			//��ֽ����ֵ��
			threshold(subMat, bny_subMat, 20, 255, CV_THRESH_BINARY);

			namedWindow("Result", WINDOW_AUTOSIZE);
			//����������
			cv::createTrackbar("threshold", "Result", &sub_threshold, 255, threshold_track);
			threshold_track(0, 0);

			imshow("frame", frame);
			waitKey(30);
		}
		cnt++;
	}

	return 0;
}

int main()
{
	bgSub_demo();
	return 0;

}