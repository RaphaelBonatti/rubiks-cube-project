#ifndef UTILS
#define UTILS

#include <string>
#include <vector>

#include "cube.hpp"

void printArray(const unsigned arr[], int n);
void printCube(const Cube &cube);
void extendVector(std::vector<unsigned> &v1, const std::vector<unsigned> &v2);
std::string getMoveName(unsigned move);
#endif