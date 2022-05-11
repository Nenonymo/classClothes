#include "pythonEmbedding.h"

using namespace std;


int callBlock(job_data* data, string blockPath)
{
    string command = "python "+ blockPath;
    string args = to_string(data->jobId) +" "+ data->tempDir +" "+ data->givenLabel;
    string line = command+" "+args;
    system(line.c_str());

    return 0;
}


int blockJob(job_data* data)
{
    #pragma omp taskgroup
    {
        //Task 1
        #pragma omp task
        {
            if (callBlock(data, "src/python/labelBlock/category.py") != 0) 
            {cout << "Error in block category" << endl; }
        }

        //Task 2
        #pragma omp task
        {
            if (callBlock(data, "src/python/labelBlock/sleeve.py") != 0) 
            {cout << "Error in block sleeve" << endl; }
        }

        //Task 3
        #pragma omp task
        {
            if (callBlock(data, "src/python/labelBlock/length.py") != 0) 
            {cout << "Error in block length" << endl; }
        }
    }
    return 0;
}

label_data* getBlockOutput(job_data* inData)
{
    string path = inData->tempDir + to_string(inData->jobId);

    label_data* outLabel = new label_data;
    outLabel->jobId = inData->jobId;

    ifstream inFile(path.c_str());

    unsigned int blockNumber;
    for (unsigned int b = 0; b<NB_BLOCK; b++)
    {
        inFile >> blockNumber;
        switch(blockNumber)
        {
            case 0: //Category
                inFile >> outLabel->category;
                break;
            case 1: //sleeves
                inFile >> outLabel->sleeveLength;
                inFile >> outLabel->sleeve;
                break;
            case 2:
                inFile >> outLabel->length;
                break;
            default:
                cout << "Error, block number unknowned" << endl;
                break;
        }
    }
    return outLabel;
}

void debugLabelData(label_data* labels)
{
    printf("Output of job #%d:\n", labels->jobId);
    printf("\tCategory: %s\n", labels->category.c_str());
    printf("\tSleeves:\n\t\tCategory: %s\n\t\tLength: %s\n", labels->sleeve.c_str(), labels->sleeveLength.c_str());
    printf("\tSize: #%d\n", labels->length);
}