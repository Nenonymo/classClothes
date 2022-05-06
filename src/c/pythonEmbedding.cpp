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
    //Section 1
    if (callBlock(data, "src/python/labelBlock/template.py") != 0) 
    {cout << "Error in block template" << endl; return -1; }

    //Section 2
    //...


    return 0;
}