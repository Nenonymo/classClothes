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

    cout << "\033]0;Labeller-Server\007" << endl;

    //Start preprocessor
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, INPUT_PREFIX, OUTPUT_PREFIX);

    cout << inFifo << " " << outFifo << endl;
    unsigned int jobId = 0;

    #pragma omp parallel num_threads(atoi(argv[3]))
    {
        #pragma omp single
        {
            //sendOut("Server initialized!", 20, outFifo);
            while (true)
            {
                cout << "inputing job #" << jobId << endl;

                //Input the job dta from the inFifo
                int outSign;
                inpData* data = new inpData;
                data->jobId = jobId;
                outSign = processInput(inFifo, outFifo, data);

                //If kill signal received or error
                if (outSign == -1)
                {break; }

                //task
                #pragma omp task
                process1Round(data, &preprocessor);
                #pragma omp taskwait
                jobId++;
            }
        }
    }
    cout << "Server stopped" << endl;
    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022