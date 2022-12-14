#pragma once
#include <opencv.hpp>

using namespace cv;
using namespace std;

void on_mouse(int EVENT, int x, int y, int flags, void* userdata);
int selectPolygon(cv::Mat srcMat, cv::Mat &dstMat);
int mouseROI();
int dftDemo(cv::Mat &mag);
int ifftDemo();
