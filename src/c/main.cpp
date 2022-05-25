#include "processesManagement.h"
#include "preprocessor.h"
#include "nnEmbedding.h"

using namespace std;

#define INPUT_PREFIX "data/Datasets_Enhancy/datasets/"
#define OUTPUT_PREFIX "Tmp/"

#define BBOX_MODEL "models/bboxRegressor.json"

int main(int argc, char* argv[])
{
    printf("Started\n");
    //input data from named pipe
    char* inFifo = argv[1];
    mkfifo(inFifo, 0666);
    char* outFifo = argv[2];
    mkfifo(outFifo, 0666);
    //Open the pipes
    //Open the input fifo
    int fdi = 0;
    fdi = open(inFifo, O_RDONLY);
    if (fdi <= 0) 
    {printf("Error, could not open the input fifo"); return -1; }

    cout << "\033]0;Labeller-Server\007" << endl;

    //Start preprocessor
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, INPUT_PREFIX, OUTPUT_PREFIX);

    //Start the bbox regressor
    NNetwork regressor = NNetwork(128*128*3, 4, BBOX_MODEL);

    cout << inFifo << " " << outFifo << endl;
    unsigned int jobId = 0;

    #pragma omp parallel num_threads(atoi(argv[3]))
    {
        #pragma omp single
        {
            //sendOut("Server initialized!", 20, outFifo);
            while (true)
            {
                cout << endl << "job #" << jobId << endl;

                //Input the job dta from the inFifo
                int outSign;
                inpData* data = new inpData;
                data->jobId = jobId;
                outSign = processInput(fdi, outFifo, data);

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
// Last modified: 11/05/2022