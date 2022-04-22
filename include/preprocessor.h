#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iostream>
#include <fstream>

class Preprocessor
{
    public:
        Preprocessor(unsigned short size[2]);
        void process(std::string path, unsigned short* bbox);
    private:
        //Innit args
        unsigned short* size;

        //Images
        cv::Mat inpImg;
        cv::Mat raw; //Raw imgage scaled and marged
        cv::Mat cropped; //Croped image scaled and marged
};

void normalInput(Preprocessor* preprocessor);
void csvInput(Preprocessor* preprocessor, std::string path);
