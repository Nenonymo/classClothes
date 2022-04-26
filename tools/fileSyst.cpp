#include "fileSyst.h"

bool doesPathExist(std::string &path)
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

int createPath(std::string &path)
{
    std::string command = "mkdir -p " + path;
    int output = system(command.c_str());
    return output;
}

int createPathIfNotExist(std::string &path)
{
    if (doesPathExist(path)) {return 0; }
    else
    {
        if (createPath(path) == 0) {return 1; }
        return 2;
    }
}