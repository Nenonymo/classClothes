#include "preprocessor.h"

using namespace std;
using namespace cv;

Preprocessor::Preprocessor(unsigned short _size[2])
{
    this->size = _size;
}

void Preprocessor::process(string path)
{
    Mat inpImg = imread(path);
    cout << inpImg.size().width << inpImg.size().height << endl;
}