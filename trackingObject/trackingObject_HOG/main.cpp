#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//��������calculateHOG
//����ͼ����ݶ�ǿ�Ⱥͷ���,��ͼ��ָ��cell������cell�ֱ����ֱ��ͼ
//src:����ͼ��
//nX��X����cell�ĸ���
//nY��Y����cell�ĸ���
//hist:����õ�ֱ��ͼ����
int calculateHOG(Mat src, int nX, int nY, float *hist)
{
	//�����������ص��ݶȼ��Ƕ�
	Mat gx, gy;
	Mat mag, angle;
	Sobel(src, gx, CV_32F, 1, 0, 1);
	Sobel(src, gy, CV_32F, 0, 1, 1);
	//x�����ݶȣ�y�����ݶȣ��ݶȣ��Ƕȣ������������or�Ƕ�
	//Ĭ���ǻ���radians��trueѡ��Ƕ�degrees
	cartToPolar(gx, gy, mag, angle, true);
	//����ÿһ��cell,����cell�ֱ����ֱ��ͼ
	for (int i = 0; i < nY; i++) {
		for (int j = 0; j < nX; j++) {
			for (int m = 0; m < 16; m++) {
				for (int n = 0; n < 16; n++) {
					//���Ƕȷ�������
					int k = (int)(angle.at<float>(i * 16 + m, j * 16 + n) / 45);
					hist[(i*nX + j) * 8 + k] += mag.at<float>(i * 16 + m, j * 16 + n);//�ۼ��ݶ�ֵ
				}
			}
		}
	}

	return 0;
}

int main()
{
	cv::Mat templateMat = cv::imread("C:\\Users\\Y\\Desktop\\template.png", 0);
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\img.png", 0);
	cv::Mat compareMat;
	//��Ҫ�Ƚϵ�ͼƬ��Сһ��
	int cellSize = 16;
	int nX = templateMat.cols / cellSize;
	int nY = templateMat.rows / cellSize;
	int bins = 8 * nX*nY;

	while (1)
	{
		float *template_hist = new float[bins];
		memset(template_hist, 0, sizeof(float)*bins);


		calculateHOG(templateMat, nX, nY, template_hist);//����ģ���ֱ��ͼ

		float distanceMin;
		Rect dstRect;

		for (int j = 0; j < srcMat.rows - templateMat.rows; j++)
		{
			for (int i = 0; i < srcMat.cols - templateMat.cols; i++)
			{
				Rect rect(i, j, templateMat.cols, templateMat.rows);
				compareMat = Mat(srcMat, rect);	//����rect�и�

				float *compare_hist = new float[bins];
				memset(compare_hist, 0, sizeof(float)*bins);

				calculateHOG(compareMat, nX, nY, compare_hist);//��Ҫ�Ƚϵ�ͼ��ֱ��ͼ

				//�ж����Ƴ̶�
				float distance = 0;
				for (int k = 0; k < bins; k++)
				{
					distance += pow(template_hist[k] - compare_hist[k], 2);
				}
				distance = sqrt(distance);
				if (j == 0) {
					distanceMin = distance;
				}
				else if (distance < distanceMin) {
					distanceMin = distance;
					dstRect = rect;
				}

				delete[] compare_hist;
				//cout << "�Ƚ�ͼ����ο�ͼ������ƶȣ�" << distance << endl;
			}
		}

		rectangle(srcMat, dstRect, Scalar(0, 0, 255));

		cv::imshow("templateMat", templateMat);
		cv::imshow("srcMat", srcMat);

		delete[] template_hist;
		
		waitKey(0);
	}

	return 0;

}