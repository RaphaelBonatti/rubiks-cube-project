#include "utils.hpp"

#include <iostream>

#include "rotation.hpp"

using std::cout;
using std::string;
using std::vector;

void printArray(const unsigned arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

void printCube(const Cube &cube) {
    printArray(cube.corner_orientation, 8);
    printArray(cube.corner_permutation, 8);
    printArray(cube.edge_orientation, 12);
    printArray(cube.edge_permutation, 12);
}

void extendVector(std::vector<unsigned> &v1, const std::vector<unsigned> &v2) {
    v1.insert(v1.end(), v2.begin(), v2.end());
}

string getMoveName(unsigned move) {
    string name(1, rotation::faces[move % 6]);
    switch (move / 6) {
        case 0:
            break;
        case 1:
            name.push_back('2');
            break;
        case 2:
            name.push_back('\'');
            break;
        default:
            throw std::invalid_argument("This move does not exist.");
    }
    return name;
}