#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include <string>

struct inputD
{
    std::string picturePath;
    std::string labelClass;
    unsigned int id;
    unsigned int priority;
};
typedef struct inputD InputData;

int killProcess();

int processInput(string& fifoPath);

InputData input1Round();