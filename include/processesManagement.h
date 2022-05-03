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
};
typedef struct inputD InputData;

int killProcess();

int processInput(char* inFifo, char* outFifo, InputData* data);

void input1Round(std::stringstream& buffer, InputData* data);

void process1Round(InputData* data);

int sendOut(const char* buffer, unsigned int buffSize, char* fifo);

bool demonize();


//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022