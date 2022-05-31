#include "processesManagement.h"
#include "preprocessor.h"
#include "nnEmbedding.h"

using namespace std;

#define INPUT_PREFIX "data/Datasets_Enhancy/datasets/"
#define OUTPUT_PREFIX "Tmp/"

int main(int argc, char* argv[])
{
    //Start the bbox regressor
    BBoxNN bbReg;
    //Start preprocessor
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, INPUT_PREFIX, OUTPUT_PREFIX);
    
    printf("Started with %d threads\n", atoi(argv[3]));
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


    cout << inFifo << " " << outFifo << endl;
    unsigned int jobId = 0;
    unsigned int jobAmount = 0;

    #pragma omp parallel num_threads(atoi(argv[3]))
    {
        #pragma omp single
        {
            //sendOut("Server initialized!", 20, outFifo);
            while (true)
            {
                //Avoid creating 5000 tasks (will result in a crash of the main app)
                //do {/*wait a bit*/ } while (jobAmount >= 16);

                cout << endl << "job #" << jobId << endl;

                #pragma omp critical
                {jobAmount++; }

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
                {process1Round(data, &preprocessor, &bbReg, &jobAmount); }

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