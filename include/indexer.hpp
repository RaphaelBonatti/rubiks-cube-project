#ifndef INDEXER
#define INDEXER

#include "cube.hpp"

namespace pruning {

struct Indexer {
    unsigned edge_orientation_index;
    unsigned edge_permutation_index;
    unsigned corner_orientation_index;
    unsigned corner_permutation_index;
    Indexer();
    Indexer(const Cube &cube);
    void indexify(const Cube &cube);
    void statify(Cube &cube);
    void indexifyEdges(const Cube &cube);
    void indexifyCorners(const Cube &cube);
    void statifyEdges(Cube &cube);
    void statifyCorners(Cube &cube);
};

unsigned udEdgesPermutationToIndex(const unsigned permutation[]);
unsigned lrEdgesPermutationToIndex(const unsigned permutation[]);
unsigned tetradsPermutationToIndex(const unsigned permutation[]);
unsigned slicesPermutationToIndex(const unsigned permutation[]);
unsigned cornersOrientationToIndex(const unsigned orientation[]);
unsigned edgesOrientationToIndex(const unsigned orientation[]);
unsigned cornersPermutationToIndex(const unsigned orientation[]);
unsigned edgesPermutationToIndex(const unsigned orientation[]);

void indexToCornerPermutation(unsigned index, unsigned permutation[]);
void indexToEdgePermutation(unsigned index, unsigned permutation[]);
void indexToCornerOrientation(unsigned index, unsigned orientation[]);
void indexToEdgeOrientation(unsigned index, unsigned orientation[]);
}  // namespace pruning

#endif
