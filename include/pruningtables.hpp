#ifndef PRUNING_TABLES
#define PRUNING_TABLES

#include "computationalrepresentation.hpp"

namespace pruning {
void generatePruningTable(ComputationalRepresentation comp_rep,
                          unsigned allowed_moves[], unsigned n_rows,
                          unsigned n_cols);
int cornersOrientationToIndex(int orientation[]);
int edgesOrientationToIndex(int orientation[]);
int cornersPermutationToIndex(int orientation[]);
int edgesPermutationToIndex(int orientation[]);
void indexToCornerOrientation(int index, int orientation[]);
void indexToEdgeOrientation(int index, int orientation[]);
void indexToCornerPermutation(int index, int permutation[]);
void indexToEdgePermutation(int index, int permutation[]);
unsigned long lehmerCodeEncode(const int permutation[], unsigned size);
void lehmerCodeDecode(int index, int permutation[], unsigned size);
} // namespace pruning

#endif