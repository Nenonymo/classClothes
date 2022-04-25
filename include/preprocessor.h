#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <iostream>
#include <fstream>
#include <algorithm>

class Preprocessor
{
    public:
        Preprocessor(unsigned short size[2], std::string inP = "", std::string outP = "");
        void process(std::string path, unsigned short* bbox);
    private:
        //Innit args
        unsigned short* size;

        //Path args
        //Picture will be inputed at the given path and outputed at the same path.
        //To sort the in different directories, use those prefixes
        std::string inPrefix;
        std::string outPrefix;
};

short unsigned* simplifyBbox(short unsigned* bbox);

cv::Mat resizeKeepRatio(cv::Mat image, short unsigned* size);

void normalInput(Preprocessor* preprocessor);
void csvInput(Preprocessor* preprocessor, std::string path);
