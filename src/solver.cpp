#include "solver.hpp"
#include "pruningtables.hpp"
#include <exception>
#include <functional>
#include <iostream>

using pruning::Indexer;
using pruning::PhaseFourTable;
using pruning::PhaseOneTable;
using pruning::PhaseRunner;
using pruning::PhaseTable;
using pruning::PhaseThreeTable;
using pruning::PhaseTwoTable;
using std::function;
using std::vector;

template <typename T> void printArray(const T arr, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << "\n";
}

void printCube(const Cube &cube) {
  printArray(cube.corner_orientation, 8);
  printArray(cube.corner_permutation, 8);
  printArray(cube.edge_orientation, 12);
  printArray(cube.edge_permutation, 12);
}
template <typename T> void appendVector(vector<T> &v1, const vector<T> &v2) {
  v1.insert(v1.end(), v2.begin(), v2.end());
}

vector<unsigned> solve(Cube cube) {
  vector<unsigned> solution = {};
  PhaseOneTable phase_one_table{};
  PhaseRunner<PhaseOneTable> phase_one_runner(phase_one_table);
  appendVector(solution, phase_one_runner.run(cube));
  PhaseTwoTable phase_two_table{};
  PhaseRunner<PhaseTwoTable> phase_two_runner(phase_two_table);
  appendVector(solution, phase_two_runner.run(cube));
  PhaseThreeTable phase_three_table{};
  PhaseRunner<PhaseThreeTable> phase_three_runner(phase_three_table);
  appendVector(solution, phase_three_runner.run(cube));
  PhaseFourTable phase_four_table{};
  PhaseRunner<PhaseFourTable> phase_four_runner(phase_four_table);
  appendVector(solution, phase_four_runner.run(cube));
  return solution;
}