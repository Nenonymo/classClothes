#include <stdio.h>
#include <string>

#include "preprocessor.h"

using namespace std;

int main(int argc, char* argv[])
{
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, "Tmp/input/", "Tmp/output/");

    normalInput(&preprocessor);
    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 25/04/2022