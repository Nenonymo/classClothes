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

void haarWavelets(Mat &src, Mat &dst, unsigned int nIter)
{
    float c, dh, dv, dd;
    assert(src.type() == CV_32FC1);
    assert(dst.type() == CV_32FC1);
    unsigned int width = src.cols;
    unsigned int height = src.rows;

    for (unsigned int k = 0; k < nIter; k++)
    {
        for (unsigned int y = 0; y < height>>(k+1); y++)
        {
            for (unsigned int x = 0; x < width>>(k+1); x++)
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

void invHaarWavelet(Mat &src, Mat &dst, unsigned int nIter, int SHRINKAGE_TYPE=0, float SHRINKAGE_T=50)
{
    float c, dh, dv, dd;
    assert(dst.type() == CV_32FC1);
    assert(src.type() == CV_32FC1);
    unsigned int width = src.cols;
    unsigned int height = src.rows;

    for (unsigned int k = nIter; k > 0; k--)
    {
        for (unsigned int y = 0; y < height>>k; y++)
        {
            for (unsigned int x = 0; x < width>>k; x++)
            {
                c = src.at<float>(y, x);
                dh = src.at<float>(y, x+(width>>k));
                dv = src.at<float>(y+(height>>k), x);
                dd = src.at<float>(y+(height>>k), x+(width>>k));

                switch (SHRINKAGE_TYPE)
                {
                    case HARD:
                        dh=hardShrink<float>(dh, SHRINKAGE_T);
                        dv=hardShrink<float>(dv, SHRINKAGE_T);
                        dd=hardShrink<float>(dd, SHRINKAGE_T);
                        break;
                    case SOFT:
                        dh=softShrink<float>(dh, SHRINKAGE_T);
                        dv=softShrink<float>(dh, SHRINKAGE_T);
                        dd=hardShrink<float>(dd, SHRINKAGE_T);
                        break;
                    case GARROT:
                        dh=garrotShrink<float>(dh, SHRINKAGE_T);
                        dv=garrotShrink<float>(dv, SHRINKAGE_T);
                        dd=garrotShrink<float>(dd, SHRINKAGE_T);
                        break;
                }
                dst.at<float>(y*2,x*2)=0.5*(c+dh+dv+dd);
                dst.at<float>(y*2,x*2+1)=0.5*(c-dh+dv-dd);
                dst.at<float>(y*2+1,x*2)=0.5*(c+dh-dv-dd);
                dst.at<float>(y*2+1,x*2+1)=0.5*(c-dh-dv+dd);
            }
        }
        Mat C=src(Rect(0,0,width>>(k-1),height>>(k-1)));
        Mat D=dst(Rect(0,0,width>>(k-1),height>>(k-1)));
        D.copyTo(C);
    }
}


void genWavelets(Mat &src, Mat &dstUnf, Mat &dstF, unsigned int nIter, int SHRINKAGE_TYPE, float SHRINKAGE_T)
{
    Mat tmp = Mat(src.cols, src.rows, CV_32FC1);
    haarWavelets(src, dstUnf, nIter);
    dstUnf.copyTo(tmp);
    invHaarWavelet(tmp, dstF, nIter, SHRINKAGE_TYPE, SHRINKAGE_T);
}



//Templates instanciation
template float sign<float>(float);
template double sign<double>(double);

template float softShrink<float>(float, float);
template double softShrink<double>(double, double);

template float hardShrink<float>(float, float);
template double hardShrink<double>(double, double);
