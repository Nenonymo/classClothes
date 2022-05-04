#include "processesManagement.h"
#include "preprocessor.h"

using namespace std;

#define INPUT_PREFIX "data/Datasets_Enhancy/datasets/"
#define OUTPUT_PREFIX "Tmp/"

int main(int argc, char* argv[])
{
    //Demonize

    //input data from named pipe
    char* inFifo = argv[1];
    mkfifo(inFifo, 0666);
    char* outFifo = argv[2];
    mkfifo(outFifo, 0666);

    //Start preprocessor
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, INPUT_PREFIX, OUTPUT_PREFIX);

    cout << inFifo << " " << outFifo << endl;
    unsigned int jobId = 0;
    //sendOut("Server initialized!", 20, outFifo);
    while (true)
    {
        cout << "inputing job #" << jobId << endl;

        int outSign;
        jobData* data = new jobData;
        data->jobId = jobId;
        outSign = processInput(inFifo, outFifo, data);

        //If kill signal received or error
        if (outSign == -1)
        {break; }

        //task
        process1Round(data, &preprocessor);
        jobId++;
    }

    for(unsigned int i = 0; i <= jobId; i++) {cleanPictures(i, &preprocessor); }
    cout << "Server stopped" << endl;

    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022