#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main() {

	std::cout << "hello opencv!" << std::endl;
	//Mat����
	cv::Mat M1(2, 2, CV_8UC3, Scalar(0, 0, 255));//2��2�У�������8λunsigned char 3ͨ��(����)
	std::cout << "M1 =" << std::endl;
	std::cout << M1 << std::endl;

	cv::Mat M2(2, 2, CV_8UC3, 1);//1 ֻ������һ��ͨ��
	std::cout << "M2 =" << std::endl;
	std::cout << M2 << std::endl;
	
	int height = M2.rows;
	int width = M2.cols;
	std::cout << "size :" << height << "," << width << std::endl;
	//Mat����
	cv::Mat M3;
	M3.create(3, 4, CV_8UC3);

	cv::Mat M4;
	cv::Mat M5;
	M4=M3;//ǳ���ƣ�ָ��ԭ����
	M3.copyTo(M5);//��ƣ�������������

	randu(M3,Scalar::all(0), Scalar::all(255));//�������ֵ������ ��Χ��0-255

	std::cout << "M3 =" << std::endl;
	std::cout << M3 << std::endl;
	std::cout << "M4 =" << std::endl;
	std::cout << M4 << std::endl;
	std::cout << "M5 =" << std::endl;
	std::cout << M5 << std::endl;

	//����Mat
	cv::Mat M6;
	cv::Mat M7;
	M6.create(3, 4, CV_8UC1);
	M7.create(3, 4, CV_8UC3);

	for (int j = 0; j < M6.rows; j++)
	{
		uchar* data = M6.ptr<uchar>(j);//ָ��M6��j�е��׵�ַ
		for (int i = 0; i < M6.cols; i++)
		{
			data[i] = j;
		}
	}
	for (int j = 0; j < M7.rows; j++)
	{
		uchar* data = M7.ptr<uchar>(j);//ָ��M7��j�е��׵�ַ
		for (int i = 0; i < M7.cols; i++)
		{
			M7.at<Vec3b>(j, i)[0] = j;//������ͨ�����з�ֵ
			M7.at<Vec3b>(j, i)[1] = j + 1;
			M7.at<Vec3b>(j, i)[2] = j + 2;
		}
	}
	std::cout << "M6 =" << std::endl;
	std::cout << M6 << std::endl;
	std::cout << "M7 =" << std::endl;
	std::cout << M7 << std::endl;

	system("pause");
	return 0;
}