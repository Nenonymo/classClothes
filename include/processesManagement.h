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

#define BUFF_SIZE 120

struct inpData
{
    unsigned int jobId;
    std::string picturePath;
    std::string labelClass;
};
typedef struct inpData inpData;

int killProcess();

int processInput(char* inFifo, char* outFifo, inpData* data);

void input1Round(std::stringstream& buffer, inpData* data);

void cleanPictures(unsigned int jobId, Preprocessor* prepro);

void process1Round(inpData* data, Preprocessor* prepro);

int sendOut(const char* buffer, unsigned int buffSize, char* fifo);

bool demonize();


//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022