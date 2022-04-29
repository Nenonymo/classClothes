#pragma once

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fcntl.h>
#include <sys/stat.h>

#define BUFF_SIZE 120

struct inputD
{
    std::string picturePath;
    std::string labelClass;
    unsigned int id;
    unsigned int priority;
};
typedef struct inputD InputData;

int killProcess();

int processInput(char* inFifo, char* outFifo);

InputData input1Round();



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022