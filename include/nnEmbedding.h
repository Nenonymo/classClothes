#pragma once

#include <fdeep/fdeep.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>

#define BBOX_MODEL "models/bboxRegressor.json"

class BBoxNN
{
    public:
        BBoxNN();
        unsigned short* predict(const char* inFilePath);

    private:
        fdeep::model myModel = fdeep::load_model(BBOX_MODEL);
};

class ClassNN
{
    public:
        ClassNN();
        unsigned int* predict(const char* inFilePath);

    private:
        fdeep::model myModel = fdeep::load_model(BBOX_MODEL);
};