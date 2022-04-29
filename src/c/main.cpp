
#include "preprocessor.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Demonize

    //input data from named pipe
    char* inFifo = "Tmp/inFifo";
    mkfifo(inFifo, 0666);

    char buff[80];
    int fd = 0;
    while(1)
    {
        fd = open(inFifo, O_RDONLY);
        read(fd, buff, 80);
        stringstream buffer;
        buffer << buff;
        string alpha;
        string beta;
        buffer >> alpha >> beta;
        cout << alpha << "; " << beta << endl;
        close(fd);
    }

    return 0;
}