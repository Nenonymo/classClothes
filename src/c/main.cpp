#include "processesManagement.h"


using namespace std;

int main(int argc, char* argv[])
{
    //Demonize

    //input data from named pipe
    char* inFifo = argv[1];
    mkfifo(inFifo, 0666);
    char* outFifo = argv[2];
    mkfifo(outFifo, 0666);

    cout << inFifo << " " << outFifo << endl;

    //sendOut("Server initialized!", 20, outFifo);
    while (true)
    {
        int outSign;
        InputData* data = new InputData;
        outSign = processInput(inFifo, outFifo, data);
        if (outSign == -1)
        {break; }
        //task
        process1Round(data);
    }
    cout << "Server stopped" << endl;

    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022