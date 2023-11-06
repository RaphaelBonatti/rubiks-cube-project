#include "solver.hpp"
#include "pruningtables.hpp"
#include <exception>
#include <functional>
#include <iostream>

using pruning::Indexer;
using std::function;
using std::vector;

// vector<unsigned> solve_phase(ComputationalRepresentation cube,
// vector<unsigned> moves, )

template <typename T>
unsigned findBestMove(const Cube cube, const T &table,
                      const vector<unsigned> &moves,
                      function<unsigned(const Cube &, const T &)> getDistance) {
  Cube temp_cube = cube;
  unsigned current_distance = getDistance(cube, table);
  std::cout << "current distance: " << current_distance << "\n";
  for (unsigned move : moves) {
    temp_cube = cube;
    temp_cube.rotate(move);
    if (getDistance(temp_cube, table) < current_distance) {
      return move;
    }
  }
  throw std::logic_error(
      "There was no 'best move'! This can be due to an wrong table value.");
}

unsigned getDistancePhaseOne(const Cube &cube, const vector<unsigned> &table) {
  return table[Indexer(cube).edge_orientation_index];
}

unsigned getDistancePhaseTwo(const Cube &cube,
                             const vector<vector<unsigned>> &table) {
  return table[Indexer(cube).corner_orientation_index]
              [pruning::udEdgesPermutationToIndex(cube.edge_permutation)];
}

unsigned getDistancePhaseThree(const Cube &cube,
                               const vector<vector<unsigned>> &table) {
  return table[Indexer(cube).corner_permutation_index]
              [pruning::lrEdgesPermutationToIndex(cube.edge_permutation)];
}

unsigned getDistancePhaseFour(const Cube &cube,
                              const vector<vector<unsigned>> &table) {
  return table[pruning::tetradsPermutationToIndex(cube.corner_permutation)]
              [pruning::slicesPermutationToIndex(cube.edge_permutation)];
}

void printArray(const int arr[], int n) {
  for (int i = n - 1; i >= 0; i--) {
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

void phaseOne(Cube &cube, vector<unsigned> &solution) {
  vector<unsigned> table_1 = pruning::PhaseOneTableGenerator().generate();
  vector<unsigned> moves_1 = {0, 1,  2,  3,  4,  5,  6,  7,  8,
                              9, 10, 11, 12, 13, 14, 15, 16, 17};

  while (getDistancePhaseOne(cube, table_1) > 0) {
    solution.push_back(findBestMove<vector<unsigned>>(cube, table_1, moves_1,
                                                      getDistancePhaseOne));
    cube.rotate(solution.back());
  }

  printCube(cube);
}

void phaseTwo(Cube &cube, vector<unsigned> &solution) {
  std::cout << "start 2\n";

  vector<vector<unsigned>> table = pruning::PhaseTwoTableGenerator().generate();
  vector<unsigned> moves_2 = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

  while (getDistancePhaseTwo(cube, table) > 0) {
    solution.push_back(findBestMove<vector<vector<unsigned>>>(
        cube, table, moves_2, getDistancePhaseTwo));
    cube.rotate(solution.back());
  }

  printCube(cube);
}

void phaseThree(Cube &cube, vector<unsigned> &solution) {
  std::cout << "start 3\n";

  vector<vector<unsigned>> table =
      pruning::PhaseThreeTableGenerator().generate();
  vector<unsigned> moves_3 = {0, 1, 6, 7, 8, 9, 10, 11, 12, 13};

  while (getDistancePhaseThree(cube, table) > 0) {
    solution.push_back(findBestMove<vector<vector<unsigned>>>(
        cube, table, moves_3, getDistancePhaseThree));
    cube.rotate(solution.back());
  }
}

void phaseFour(Cube &cube, vector<unsigned> &solution) {
  std::cout << "start 4\n";

  vector<vector<unsigned>> table =
      pruning::PhaseFourTableGenerator().generate();
  vector<unsigned> moves_4 = {6, 7, 8, 9, 10, 11};

  while (getDistancePhaseFour(cube, table) > 0) {
    solution.push_back(findBestMove<vector<vector<unsigned>>>(
        cube, table, moves_4, getDistancePhaseFour));
    cube.rotate(solution.back());
  }

  printCube(cube);
}

vector<unsigned> solve(Cube cube) {
  vector<unsigned> solution;
  phaseOne(cube, solution);
  phaseTwo(cube, solution);
  phaseThree(cube, solution);
  phaseFour(cube, solution);
  return solution;
}