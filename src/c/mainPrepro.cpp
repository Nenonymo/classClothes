#include <stdio.h>
#include <string>

#include "preprocessor.h"

using namespace std;

#define INPUT_PREFIX "../data/Datasets_Enhancy/datasets/"
#define OUTPUT_PREFIX "../data/Datasets_Enhancy/processed/"

int main(int argc, char* argv[])
{
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size, INPUT_PREFIX, OUTPUT_PREFIX);

    normalInput(&preprocessor);
    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 27/04/2022