#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "fileSyst.h"
#include "wavelet.h"

class Preprocessor
{
    public:
        Preprocessor(unsigned short size[2], std::string inP = "", std::string outP = "");
        void process(unsigned int id, std::string path, unsigned short* bbox);
        void processWithoutBbox(unsigned int id, std::string path);

        std::string getOutPath();
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

void csvInput(Preprocessor* preprocessor, std::string path);



//Code written by:
//      - Nemo Chentre
//
// Last modified: 25/04/2022