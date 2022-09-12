#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Y\\Desktop\\coin.png", 0);//��ȡͼƬֱ��ת��Ϊ�Ҷ�ͼ
	cv::Mat binaryMat;//��ֵͼ
	cv::Mat labelMat;//��ǩ
	cv::Mat statsMat;//״̬����
	cv::Mat centrMat;//��ͨ������
	cv::Mat resultMat;//���

	threshold(srcMat, binaryMat, 100, 255, THRESH_BINARY);//��򷨶�ֵ��

	//�����ͨ�� ����ֵΪ��ͨ�����
	int numComp = connectedComponentsWithStats(binaryMat, labelMat, statsMat, centrMat, 8, CV_32S);
	binaryMat.copyTo(resultMat);

	//����bounding box
	for (int i = 1; i < numComp; i++)
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
	}

	imshow("��ֵͼ", binaryMat);
	imshow("���ͼ", resultMat);

	cout << "Ӳ�Ҹ�����" << numComp - 1 << endl;

	waitKey(0);

	return 0;

}


