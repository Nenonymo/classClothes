#include "processesManagement.h"

using namespace std;

int killProcess();

int processInput(char* inFifo, char* outFifo)
{
   //Input data
    //Open the input fifo
    int fdi = 0;
    fdi = open(inFifo, O_RDONLY, O_NONBLOCK);
    if (fdi <= 0) 
    {
        cout << "Error, could not open the input fifo" << endl;
        return -1;
    }

    //Input the data from the in Fifo
    char* cBuff;
    read(fdi, cBuff, BUFF_SIZE);
    stringstream buffer;
    buffer << cBuff; //Transform the buffer into a stream

    //Process the signal attached to the communication
    //The signal defines the kind of communication.
    //  0 = Data to process
    //  1 = Kill the server
    //  2 = Undefined
    int signal;
    buffer >> signal;
    if (signal == -1) //Kill signal
    {killProcess(); 
    return 1; }
    else if (signal != 0) //Yet unedefined signal
    {return 2; }

    InputData data;
    buffer >> data.picturePath;
    buffer >> data.labelClass;


   //Send confirmation of processing to outFifo
    //Open the output fifo
    int fdo = 0;
    fdo = open(outFifo, O_WRONLY);
    if (fdo <= 0)
    {
        cout << "Error, could not open the output fifo" << endl;
        return -1;
    }
    char outBuff[] = "Data received and queued for processing...";
    write(fdo, outBuff, sizeof(outBuff)+1);
    close(fdo);
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022