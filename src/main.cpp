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
    char arr[48] = {'R', 'L', 'R', 'D', 'L', 'D', 'L', 'L', 'U', 'B', 'R', 'L',
                    'U', 'L', 'B', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
                    'U', 'U', 'D', 'D', 'R', 'U', 'U', 'L', 'B', 'B', 'B', 'B',
                    'D', 'D', 'D', 'U', 'D', 'R', 'R', 'U', 'R', 'B', 'R', 'B'};
    Cube cube(arr);
    assert(cube.checkCombination());
    vector<unsigned> solution = solve(cube);
    for (unsigned move : solution) {
        cout << getMoveName(move) << " ";
    }
    cout << "\n";
    return 0;
}