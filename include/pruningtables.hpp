#ifndef PRUNING_TABLES
#define PRUNING_TABLES

namespace pruning {
int cornersOrientationToIndex(int orientation[]);
int edgesOrientationToIndex(int orientation[]);
int cornersPermutationToIndex(int orientation[]);
int edgesPermutationToIndex(int orientation[]);
unsigned long lehmerCodeEncode(const int permutation[], unsigned size);
} // namespace pruning

#endif