#include "processesManagement.h"

using namespace std;

int killProcess();

int processInput(char* inFifo, char* outFifo, jobData* data)
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
    char cBuff[BUFF_SIZE];
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
    if (signal == 1) //Kill signal
    {
        killProcess();
        sendOut("server shutdowned.", 18, outFifo);
        return -1; 
    }
    else if (signal != 0) //Yet unedefined signal
    {return -1; }

    input1Round(buffer, data);


   //Send confirmation of processing to outFifo
    sendOut("communication received, data queued for processing.", 51, outFifo);
    return 0;
}

void input1Round(stringstream& buffer, jobData* data)
{
    buffer >> data->picturePath;
    buffer >> data->labelClass;
}

void cleanPictures(unsigned int jobId, Preprocessor* prepro)
{
    string outP = prepro->getOutPath();
    string filename = outP + "gray_" + to_string(jobId) + ".bmp";
    remove(filename.c_str());
    filename = outP + "crop_" + to_string(jobId) + ".bmp";
    remove(filename.c_str());
    filename = outP + "wav1_" + to_string(jobId) + ".bmp";
    remove(filename.c_str());
    filename = outP + "wav2_" + to_string(jobId) + ".bmp";
    remove(filename.c_str());
}

void process1Round(jobData* data, Preprocessor* prepro)
{
    //work
    printf("processing picture %s with arg %s\n", data->picturePath.c_str(), data->labelClass.c_str());
    
    prepro->processWithoutBbox(data->jobId, data->picturePath);

    printf("Picture preprocessed\n");
    
    delete data;
}

int sendOut(const char* buffer, unsigned int buffSize, char* fifo)
{
    int fdo = 0;
    fdo = open(fifo, O_WRONLY);
    if (fdo <= 0)
    {
        cout << "Error, could not open the output fifo" << endl;
        return -1;
    }
    write(fdo, buffer, buffSize);
    close(fdo);
    return 0;
}

int killProcess()
{
    return 0;
}


/*
bool demonize()
{
    (void) uchdir("/");

    if(int fdnull = open("dev/null", O_RDWR))
    {
        dup2 (fdnull, STDIN_FILENO);
        dup2 (fdnull, STDOUT_FILENO);
        dup2 (fdnull, STDERR_FILENO);
        close(fdnull);
    }
    else
    {
        //Do something
    }
}*/




//Code written by:
//      - Nemo Chentre
//
// Last modified: 29/04/2022