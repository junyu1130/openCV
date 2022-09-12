#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat bgFrame;

int createMaskByKmeans(cv::Mat src, cv::Mat &mask)
{
	if ((mask.type() != CV_8UC1) || (src.size() != mask.size())) {
		return 0;
	}

	int width = src.cols;
	int height = src.rows;
	int pixNum = width * height;
	int clusterCount = 2;

	Mat labels;
	Mat centers;

	//����Kmeans�õ�����
	Mat sampleData = src.reshape(3, pixNum);
	Mat km_data;
	sampleData.convertTo(km_data, CV_32F);

	//ִ��Kmeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(km_data, clusterCount, labels, criteria, clusterCount, KMEANS_PP_CENTERS, centers);

	//����mask
	uchar fg[2] = { 0,255 };
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			mask.at<uchar>(row, col) = fg[labels.at<int>(row*width + col)];
		}
	}

	return 0;
}


//ͨ����ɫ���˵õ�������Ϊ��ͨ��ͼ��
Mat replace_and_blend(Mat &frame, Mat &mask)
{
	Mat result;
	int rows = frame.rows;
	int cols = frame.cols;
	result = Mat::zeros(frame.size(), frame.type());
	for (int i = 0; i < rows; i++)
	{
		uchar *pf = frame.ptr(i);//����ǰ��
		uchar *pm = mask.ptr(i);//����
		uchar *pb = bgFrame.ptr(i);//����
		uchar *pr = result.ptr(i);//���

		for (int j = 0; j < cols; j++)
		{
			pm++;
			if (*pm == 255)//����
			{
				pr[3 * j] = pb[3 * j];
				pr[3 * j + 1] = pb[3 * j + 1];
				pr[3 * j + 2] = pb[3 * j + 2];
			}
			else if (*pm == 0)//ǰ��
			{
				pr[3 * j] = pf[3 * j];
				pr[3 * j + 1] = pf[3 * j + 1];
				pr[3 * j + 2] = pf[3 * j + 2];
			}
			else //�ںϲ���
			{
				int m = *pm;
				double w = m / 255.0;
				pr[3 * j] = w * pb[3 * j] + (1 - w) * pf[3 * j];
				pr[3 * j + 1] = w * pb[3 * j + 1] + (1 - w) * pf[3 * j + 1];
				pr[3 * j + 2] = w * pb[3 * j + 2] + (1 - w) * pf[3 * j + 2];
				//����ȡǰ���ͱ�����ƽ��ֵ
				/*pr[3 * j] = (pb[3 * j] +  pf[3 * j])/2;
				pr[3 * j + 1] = (pb[3 * j + 1] +  pf[3 * j + 1])/2;
				pr[3 * j + 2] = (pb[3 * j + 2] +  pf[3 * j + 2])/2;*/
			}
		}
	}
	return result;
}

int movieKmeans(VideoCapture capVideo, VideoCapture background)
{
	Mat frame;
	Mat dstframe;
	Mat hsv;

	int cnt = 0;
	int totalFrames = background.get(CV_CAP_PROP_FRAME_COUNT);
	cout << totalFrames << endl;
	
	while (1)
	{
		if (!capVideo.read(frame))
		{
			cout << "��Ƶ�������" << endl;
			return -1;
		}
		
		background >> bgFrame;
		if (cnt == totalFrames - 10)
		{
			background.set(CV_CAP_PROP_POS_FRAMES, 0);
			cnt = 0;
		}

		resize(bgFrame, bgFrame, Size(frame.cols, frame.rows));   //ʹ����ͼ����Ƶ�زĴ�С��ͬ

		Mat maskMat = Mat::zeros(frame.size(), CV_8UC1);
		//createMaskByKmeans(frame, maskMat);
		cvtColor(frame, hsv, COLOR_BGR2HSV);//ת����HSV
		inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), maskMat);
		Mat k = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
		//��̬ѧ����
		morphologyEx(maskMat, maskMat, MORPH_CLOSE, k);
		GaussianBlur(maskMat, maskMat, Size(3, 3), 0, 0);
		dstframe = replace_and_blend(frame, maskMat);

		imshow("ԭʼ��Ƶ", frame);
		imshow("mask", maskMat);
		imshow("Ч����Ƶ", dstframe);

		cnt++;
		waitKey(30);
	}
	
	return 0;
}



int main()
{
	//cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\movie.jpg");
	//cv::Mat maskMat = Mat::zeros(srcMat.size(), CV_8UC1);

	//createMaskByKmeans(srcMat, maskMat);
	//cv::imshow("srcMat", srcMat);
	//cv::imshow("maskMat", maskMat);

	VideoCapture capVideo1;
	capVideo1.open("..\\dragon.mp4");
	VideoCapture capVideo_bg;
	capVideo_bg.open("..\\bg.mp4");

	

	movieKmeans(capVideo1, capVideo_bg);


	waitKey(0);

	return 0;

}