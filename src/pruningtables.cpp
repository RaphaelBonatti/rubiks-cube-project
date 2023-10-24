#include "pruningtables.hpp"
#include "computationalrepresentation.hpp"
#include <array>
#include <iterator>
#include <vector>

using std::array;
using std::vector;

void pruning::generatePruningTable(ComputationalRepresentation comp_rep,
                                   unsigned allowed_moves[],
                                   const unsigned n_rows,
                                   const unsigned n_cols) {
  vector<unsigned[2]> stack;
  vector<vector<unsigned>> table(n_rows, std::vector<unsigned>(n_cols, -1));
  unsigned d = 0;
}

int pruning::cornersOrientationToIndex(int orientation[]) {
  int index = 0;
  for (int i = 0; i < 8; ++i) {
    index = index * 3 + orientation[i];
  }
  return index;
}

int pruning::edgesOrientationToIndex(int orientation[]) {
  int index = 0;
  for (int i = 0; i < 12; ++i) {
    index = index * 2 + orientation[i];
  }
  return index;
}

unsigned long pruning::lehmerCodeEncode(const int permutation[],
                                        unsigned size) {
  unsigned long result = 0;
  for (int i = 0; i < size - 1; ++i) {
    for (int j = i + 1; j < size; ++j) {
      result = result + int(permutation[i] > permutation[j]);
    }
    result *= size - 1 - i;
  }
  return result;
}

int pruning::cornersPermutationToIndex(int permutation[]) {
  return lehmerCodeEncode(permutation, 8);
}

int pruning::edgesPermutationToIndex(int permutation[]) {
  return lehmerCodeEncode(permutation, 12);
}

void pruning::indexToCornerOrientation(int index, int orientation[]) {
  for (int i = 7; i >= 0; --i) {
    orientation[i] = index % 3;
    index = (index - orientation[i]) / 3;
  }
}

void pruning::indexToEdgeOrientation(int index, int orientation[]) {
  for (int i = 11; i >= 0; --i) {
    orientation[i] = index % 2;
    index = (index - orientation[i]) / 2;
  }
}

void pruning::lehmerCodeDecode(int index, int permutation[], unsigned size) {
  permutation[size - 1] = 1;
  for (int i = size - 2; i >= 0; --i) {
    permutation[i] = 1 + (index % (size - i));
    index = (index - (index % (size - i))) / (size - i);
    for (int j = i + 1; j < size; ++j) {
      permutation[j] = permutation[j] + int(permutation[j] >= permutation[i]);
    }
  }
}

void pruning::indexToCornerPermutation(int index, int permutation[]) {
  lehmerCodeDecode(index, permutation, 8);
}

void pruning::indexToEdgePermutation(int index, int permutation[]) {
  lehmerCodeDecode(index, permutation, 12);
}