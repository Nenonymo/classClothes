#pragma once

#include <opencv2/opencv.hpp>

#define NONE 0
#define HARD 1
#define SOFT 2
#define GARROT 3


void genWavelets(cv::Mat &src, cv::Mat &dstV, cv::Mat &dstH, unsigned int nIter, int SHRINKAGE_TYPE, float SHRINKAGE_T);