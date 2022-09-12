#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	VideoCapture capVideo(0); //��������ͷ

	//�����Ƶ��ʧ��
	if (!capVideo.isOpened()) {
		std::cout << "Unable to open video!" << std::endl;
		return -1;
	}

	Mat frame;
	Mat tempMat;
	Mat refMat;
	Mat resultMat;
	Mat dispMat;

	int cnt = 0;

	while (1)
	{
		capVideo >> frame;
		if (frame.empty()) break;

		//���ѡȡģ��
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}

		int match_method = 0;
		matchTemplate(frame, refMat, resultMat, match_method);//����ģ��ƥ��

		normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());//��һ��

		double minVal; double maxVal; Point minLoc; Point maxLoc;
		Point matchLoc;

		minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());//Ѱ�Ҽ�ֵ

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else {
			matchLoc = maxLoc;
		}

		frame.copyTo(dispMat);
		rectangle(dispMat, matchLoc, Point(matchLoc.x + refMat.cols, matchLoc.y + refMat.rows), Scalar::all(0), 2, 8, 0);

		cnt++;
		cv::imshow("frame", frame);
		cv::imshow("dispMat", dispMat);

		waitKey(30);
	}

	return 0;

}