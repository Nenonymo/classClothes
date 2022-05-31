#pragma once

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

#include "preprocessor.h"
#include "pythonEmbedding.h"
#include "nnEmbedding.h"
#include "fileSyst.h"

#define BUFF_SIZE 200

struct inpData
{
    unsigned int jobId;
    std::string picturePath;
    std::string labelClass;
};
typedef struct inpData inpData;

inline int killProcess();

int processInput(int inFifo, const char* outFifo, inpData* data);

inline void input1Round(std::stringstream& buffer, inpData* data);

inline void cleanPictures(unsigned int jobId, Preprocessor* prepro);

void process1Round(inpData* data, Preprocessor* prepro, BBoxNN* bboxReg, unsigned int* jobA);

inline int sendOut(const char* buffer, unsigned int buffSize, const char* outFifo);

bool demonize();


//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022