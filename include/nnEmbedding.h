#include <fdeep/fdeep.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>

#define BBOX_MODEL "models/bboxRegressor.json"

class NNetwork
{
    public:
        NNetwork(unsigned int dimIn, unsigned int dimOut, char* path);
        unsigned short* predict(char* inFilePath);

    private:
        unsigned int dimIn, dimOut;
        fdeep::model myModel = fdeep::load_model(BBOX_MODEL);
};