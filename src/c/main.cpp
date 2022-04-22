#include <stdio.h>
#include <string>

#include "preprocessor.h"

using namespace std;

int main(int argc, char* argv[])
{
    unsigned short size[] = {128, 128};
    Preprocessor preprocessor(size);

    string path;
    cin >> path;
    preprocessor.process(path);

    return 0;
}