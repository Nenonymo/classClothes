#include "processesManagement.h"

using namespace std;

int killProcess();

int processInput(string& fifoPath)
{
    int fd = 0;
    fd = open(fifoPath.c_str(), O_RDONLY, O_NONBLOCK);
    if (fd <= 0) 
    {
        cout << "Error, could not open the fifo" << endl;
        return -1;
    }


}