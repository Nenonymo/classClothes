#pragma once
#include <stdio.h>
#include <python3.10/Python.h>
#include <string>
#include <iostream>

typedef struct job_data
{
    unsigned int jobId;
    const char* tempDir;
    const char* givenLabel;
} job_data;

int blockJob(struct job_data* data);
