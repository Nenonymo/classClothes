#include <stdio.h>
#include <string>

#include "preprocessor.h"

using namespace std;

int main(int argc, char* argv[])
{
    unsigned short size[] = {516, 516};
    Preprocessor preprocessor(size, "data/Datasets_Enhancy/datasets/", "data/Datasets_Enhancy/processed/");

    normalInput(&preprocessor);
    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 25/04/2022