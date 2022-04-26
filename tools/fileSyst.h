#pragma once

#include <sys/stat.h>
#include <stdlib.h>
#include <string>

bool doesPathExist(std::string &path);

int createPath(std::string &path);

int createPathIfNotExist(std::string &path);