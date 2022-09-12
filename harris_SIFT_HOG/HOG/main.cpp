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
	cv::Mat srcMat = cv::imread("C:\\Users\\Y\\Desktop\\hogTemplate.jpg", 0);
	cv::Mat compareMat1 = cv::imread("C:\\Users\\Y\\Desktop\\img1.jpg", 0);
	cv::Mat compareMat2 = cv::imread("C:\\Users\\Y\\Desktop\\img2.jpg", 0);
	//��Ҫ�Ƚϵ�ͼƬ��Сһ��
	int cellSize = 16;
	int nX = srcMat.cols / cellSize;
	int nY = srcMat.rows / cellSize;
	int bins = 8 * nX*nY;
	
	while (1)
	{
		float *src_hist = new float[bins];
		memset(src_hist, 0, sizeof(float)*bins);
		float *compare_hist1 = new float[bins];
		memset(compare_hist1, 0, sizeof(float)*bins);
		float *compare_hist2 = new float[bins];
		memset(compare_hist2, 0, sizeof(float)*bins);

		calculateHOG(srcMat, nX, nY, src_hist);//����ԭͼ��ֱ��ͼ
		calculateHOG(compareMat1, nX, nY, compare_hist1);//�Ƚ�ͼ1��ֱ��ͼ
		calculateHOG(compareMat2, nX, nY, compare_hist2);//�Ƚ�ͼ2��ֱ��ͼ

		//�ж����Ƴ̶�
		float distance1 = 0;
		float distance2 = 0;
		for (int i = 0; i < bins; i++)
		{
			distance1 += pow(src_hist[i] - compare_hist1[i], 2);
			distance2 += pow(src_hist[i] - compare_hist2[i], 2);
		}
		distance1 = sqrt(distance1);
		distance2 = sqrt(distance2);
		cout << "ͼ��1��ο�ͼ������ƶȣ�" << distance1 << endl;
		cout << "ͼ��2��ο�ͼ������ƶȣ�" << distance2 << endl;
		if (distance1 < distance2) {
			cout << "ͼ��1��ο�ͼ�������" << endl;
		}
		else {
			cout << "ͼ��2��ο�ͼ�������" << endl;
		}

		cv::imshow("srcMat", srcMat);
		cv::imshow("compareMat1", compareMat1);
		cv::imshow("compareMat2", compareMat2);
		delete[] src_hist;
		delete[] compare_hist1;
		delete[] compare_hist2;
		waitKey(0);
	}

	return 0;

}