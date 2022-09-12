#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\clip.png", 0);//��ȡͼƬֱ��ת��Ϊ�Ҷ�ͼ
	cv::Mat binaryMat;//��ֵͼ
	cv::Mat openMat;//������
	cv::Mat labelMat;//��ǩ
	cv::Mat statsMat;//״̬����
	cv::Mat centrMat;//��ͨ������
	cv::Mat resultMat;//���

	threshold(srcMat, binaryMat, 100, 255, THRESH_BINARY_INV);//��򷨶�ֵ��

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));//�ṹԪ��
	morphologyEx(binaryMat, openMat, MORPH_OPEN, kernel);//������

	//�����ͨ�� ����ֵΪ��ͨ�����
	int numComp = connectedComponentsWithStats(openMat, labelMat, statsMat, centrMat, 8, CV_32S);

	openMat.copyTo(resultMat);

	int num = 0;
	//����bounding box
	for (int i = 1; i < numComp; i++)
	{
		int area = statsMat.at<int>(i, 2) * statsMat.at<int>(i, 3);
		if (area > 15000 && area < 39000)
		{
			Rect bndbox;
			//bounding box���Ͻ�����
			bndbox.x = statsMat.at<int>(i, 0);
			bndbox.y = statsMat.at<int>(i, 1);
			//bouding box�Ŀ�ͳ� 
			bndbox.width = statsMat.at<int>(i, 2);
			bndbox.height = statsMat.at<int>(i, 3);
			//����
			rectangle(resultMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
			//��ͨ����

			num++;
		}
	}

	imshow("��ֵͼ", binaryMat);
	imshow("������", openMat);
	imshow("���ͼ", resultMat);

	cout << "�����������" << num << endl;

	waitKey(0);

	return 0;

}


