#include "pruningtables.hpp"
#include <iterator>
#include <vector>

using std::vector;

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