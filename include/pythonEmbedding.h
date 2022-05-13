#pragma once
#include <stdio.h>
#include <python3.10/Python.h>
#include <string>
#include <iostream>
#include <fstream>

#define PY_BUFF_SIZE 120
#define NB_BLOCK 3

typedef struct job_data
{
    unsigned int jobId;
    const char* tempDir;
    const char* givenLabel;
} job_data;

typedef struct label_data
{
    unsigned int jobId;
    std::string category;
    std::string sleeveLength;
    std::string sleeve;
    short unsigned int length;
} label_data;

int blockJob(struct job_data* data);
label_data* getBlockOutput(struct job_data* inData);
void debugLabelData(label_data* labels);
