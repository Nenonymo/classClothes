#include "wavelet.h"

using namespace std;
using namespace cv;

template <typename T>
T sign(T x)
{
    if (x == 0) {return 0; }
    else if (x < 0) {return -1; }
    else {return 1; }
}

template <typename T>
T softShrink(T d, T t)
{
    if (fabs(d)<=t) {return 0; }
    return sign<T>(d)*(fabs(d)-t);
}

template <typename T>
T hardShrink(T d, T t)
{
    if (fabs(d)<=t) {return 0; }
    return d;
}

template <typename T>
T garrotShrink(T d, T t)
{
    if (fabs(d)<=t) {return 0; }
    return (d - ((t*t)/d));
}

void genWavelets(Mat &src, Mat &dst, unsigned int nIter)
{
    float c, dh, dv, dd;
    assert(src.type() == CV_32FC1);
    assert(dst.type() == CV_32FC1);
    unsigned int width = src.cols;
    unsigned int height = src.rows;

    for (unsigned int k = 0; k < nIter; k++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            for (unsigned int x = 0; x < width; x++)
            {
                c=(src.at<float>(2*y,2*x)+src.at<float>(2*y,2*x+1)+src.at<float>(2*y+1,2*x)+src.at<float>(2*y+1,2*x+1))*0.5;
                dst.at<float>(y,x)=c;

                dh=(src.at<float>(2*y,2*x)+src.at<float>(2*y+1,2*x)-src.at<float>(2*y,2*x+1)-src.at<float>(2*y+1,2*x+1))*0.5;
                dst.at<float>(y,x+(width>>(k+1)))=dh;

                dv=(src.at<float>(2*y,2*x)+src.at<float>(2*y,2*x+1)-src.at<float>(2*y+1,2*x)-src.at<float>(2*y+1,2*x+1))*0.5;
                dst.at<float>(y+(height>>(k+1)),x)=dv;

                dd=(src.at<float>(2*y,2*x)-src.at<float>(2*y,2*x+1)-src.at<float>(2*y+1,2*x)+src.at<float>(2*y+1,2*x+1))*0.5;
                dst.at<float>(y+(height>>(k+1)),x+(width>>(k+1)))=dd;
            }
        }
        dst.copyTo(src);
    }
}









//Templates instanciation
template float sign<float>(float);
template double sign<double>(double);

template float softShrink<float>(float, float);
template double softShrink<double>(double, double);

template float hardShrink<float>(float, float);
template double hardShrink<double>(double, double);
