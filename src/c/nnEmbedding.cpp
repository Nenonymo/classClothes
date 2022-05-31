#include "nnEmbedding.h"

using namespace std;
using namespace cv;

BBoxNN::BBoxNN()
{
    cout << "NN loaded." << endl;
}
;

unsigned short* BBoxNN::predict(const char* inFilePath)
{
    Mat fIm = imread(inFilePath);
    Mat image;
    resize(fIm, image, Size(224, 224), INTER_LINEAR);

    const auto input = fdeep::tensor_from_bytes(image.ptr(),
        static_cast<std::size_t>(image.rows),
        static_cast<std::size_t>(image.cols),
        static_cast<std::size_t>(image.channels()),
        0.0f, 1.0f);

    auto result = this->myModel.predict({ input });
    cout << fdeep::show_tensors(result) << endl;
    //const std::vector<float> vec = result.to_vector();


    unsigned short* bbox = new unsigned short[4];
    /*for (int i = 0; i < 4; i++)
    {
        bbox[i] = (unsigned int)(vec[i] * 224.0f);
    }

    printf("Item found in boundarybox (%d; %d; %d; %d)\n", 
        bbox[0], bbox[1], bbox[2], bbox[3]);*/

    return bbox;
}

unsigned int* ClassNN::predict(const char* inFilePath)
{
    Mat fIm = imread(inFilePath);
    Mat image;
    resize(fIm, image, Size(224, 224), INTER_LINEAR);

    const auto input = fdeep::tensor_from_bytes(image.ptr(),
        static_cast<std::size_t>(image.rows),
        static_cast<std::size_t>(image.cols),
        static_cast<std::size_t>(image.channels()),
        0.0f, 1.0f);

    auto result = this->myModel.predict({ input });
    cout << fdeep::show_tensors(result) << endl;

    return NULL;
}

