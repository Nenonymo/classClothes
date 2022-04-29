#include "processesManagement.h"


using namespace std;

int main(int argc, char* argv[])
{
    //Demonize

    //input data from named pipe
    char* inFifo = "Tmp/inFifo";
    mkfifo(inFifo, 0666);
    char* outFifo = "Tmp/outFifo";
    mkfifo(outFifo, 0666);

    int outSign;
    outSign = processInput(inFifo, outFifo);

    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022