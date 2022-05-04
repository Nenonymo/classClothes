#pragma once

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

#include "preprocessor.h"

#define BUFF_SIZE 120

struct jobData
{
    unsigned int jobId;
    std::string picturePath;
    std::string labelClass;
};
typedef struct jobData jobData;

int killProcess();

int processInput(char* inFifo, char* outFifo, jobData* data);

void input1Round(std::stringstream& buffer, jobData* data);

void cleanPictures(unsigned int jobId, Preprocessor* prepro);

void process1Round(jobData* data, Preprocessor* prepro);

int sendOut(const char* buffer, unsigned int buffSize, char* fifo);

bool demonize();


//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022