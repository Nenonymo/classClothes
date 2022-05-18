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

    unsigned int n;
    unsigned int id;
    string file;
    cin >> n;

    unsigned int numThread = 1;
    if (argc >= 2) {numThread = atoi(argv[1]); }

    #pragma omp parallel for schedule(dynamic) num_threads(numThread)
    for (unsigned int i = 0; i < n; i++)
    {
        short unsigned* bbox = new short unsigned[8]; //deallocated in simplifyBboxa
        if (i%(n/80) == 0)
        {cout << "[" << string(((i/(double)n))*80, '#') << string(((1-(i/(double)n))*80), ' ') << "]" << endl;}
        #pragma omp critical
        {
            cin >> id;
            cin >> file;
            for (unsigned int j = 0; j < 8; j++) {cin >> bbox[j]; }
        }
        preprocessor.process(id, file, bbox);
    }

    printf("Done");

    return 0;
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 27/04/2022