#include "nnEmbedding.h"

using namespace std;
using namespace fdeep;

model loadModel(char* path)
{
    const auto mod = load_model(path);
    return mod;
}

NNetwork::NNetwork(unsigned int dimIn, unsigned int dimOut, char* path)
{
    this->dimIn = dimIn;
    this->dimOut = dimOut;
    printf("Loading model \"%s\"\n", path);
    printf("Model loaded.\n");
}

unsigned short* NNetwork::predict(char* inFilePath)
{
    const cv::Mat image = cv::imread(inFilePath);
    cv::resize(image, image, cv::size(224, 224));
    return NULL;
}

