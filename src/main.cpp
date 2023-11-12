#include <assert.h>

#include <iostream>
#include <string>

#include "rotation.hpp"
#include "solver.hpp"
#include "utils.hpp"

using std::cout;
using std::string;
using std::vector;

int main() {
    char arr[48] = {'F', 'U', 'U', 'U', 'B', 'D', 'U', 'U', 'L', 'R', 'L', 'L',
                    'L', 'L', 'L', 'R', 'B', 'F', 'F', 'D', 'F', 'B', 'F', 'D',
                    'R', 'R', 'R', 'R', 'L', 'L', 'R', 'R', 'B', 'B', 'U', 'U',
                    'F', 'D', 'B', 'U', 'D', 'D', 'F', 'B', 'D', 'B', 'D', 'F'};
    Cube cube(arr);
    assert(cube.checkCombination());
    vector<unsigned> solution = solve(cube);
    for (unsigned move : solution) {
        cout << getMoveName(move) << " ";
    }
    cout << "\n";
    return 0;
}