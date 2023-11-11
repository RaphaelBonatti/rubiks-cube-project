#include "indexer.hpp"

#include <algorithm>

#include "lehmercode.hpp"

using pruning::Indexer;

Indexer::Indexer()
    : edge_orientation_index(0),
      edge_permutation_index(0),
      corner_orientation_index(0),
      corner_permutation_index(0){};

Indexer::Indexer(const Cube &cube) { indexify(cube); }

void Indexer::indexify(const Cube &cube) {
    indexifyEdges(cube);
    indexifyCorners(cube);
}

void Indexer::statify(Cube &cube) {
    statifyEdges(cube);
    statifyCorners(cube);
}

void Indexer::indexifyEdges(const Cube &cube) {
    edge_orientation_index = edgesOrientationToIndex(cube.edge_orientation);
    edge_permutation_index = edgesPermutationToIndex(cube.edge_permutation);
}

void Indexer::indexifyCorners(const Cube &cube) {
    corner_orientation_index = cornersOrientationToIndex(cube.corner_orientation);
    corner_permutation_index = cornersPermutationToIndex(cube.corner_permutation);
}

void Indexer::statifyEdges(Cube &cube) {
    indexToEdgeOrientation(edge_orientation_index, cube.edge_orientation);
    indexToEdgePermutation(edge_permutation_index, cube.edge_permutation);
}

void Indexer::statifyCorners(Cube &cube) {
    indexToCornerOrientation(corner_orientation_index, cube.corner_orientation);
    indexToCornerPermutation(corner_permutation_index, cube.corner_permutation);
}

unsigned nChooseK(unsigned n, unsigned k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    int result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

unsigned pruning::udEdgesPermutationToIndex(const unsigned permutation[]) {
    unsigned index = 0;
    unsigned r = 4;
    for (int i = 11; i >= 0; --i) {
        if ((permutation[i] - 1) / 4 == 1) {
            index += nChooseK(i, r);
            --r;
        }
    }
    return index;
}

unsigned pruning::lrEdgesPermutationToIndex(const unsigned permutation[]) {
    unsigned mask[8] = {0, 1, 2, 3, 8, 9, 10, 11};
    unsigned index = 0;
    unsigned r = 4;
    for (int i = 7; i >= 0; --i) {
        if ((permutation[mask[i]] - 1) % 2 == 0) {
            index += nChooseK(i, r);
            --r;
        }
    }
    return index;
}

unsigned pruning::tetradsPermutationToIndex(const unsigned permutation[]) {
    unsigned tetrad_1[4] = {permutation[0], permutation[2], permutation[5], permutation[7]};
    unsigned tetrad_2[4] = {permutation[1], permutation[3], permutation[4], permutation[6]};
    unsigned tetrad_1_permutation_index = lehmerCodeEncode(tetrad_1, 4);
    unsigned tetrad_2_position_index = std::find(tetrad_2, tetrad_2 + 4, 2) - tetrad_2;
    return tetrad_1_permutation_index + 24 * tetrad_2_position_index;
}

unsigned pruning::slicesPermutationToIndex(const unsigned permutation[]) {
    unsigned slice_1[4] = {permutation[0], permutation[2], permutation[8], permutation[10]};
    unsigned slice_2[4] = {permutation[4], permutation[5], permutation[6], permutation[7]};
    unsigned slice_3[4] = {permutation[1], permutation[3], permutation[9], permutation[11]};
    unsigned slice_1_index = lehmerCodeEncode(slice_1, 4);
    unsigned slice_2_index = lehmerCodeEncode(slice_2, 4);
    unsigned slice_3_index = 0;
    unsigned r = 2;
    unsigned last = 0;
    for (int i = 3; i >= 0; --i) {
        if (slice_3[i] < 5) {
            slice_3_index += nChooseK(i, r);
            --r;
            last = slice_3[i];
        }
    }
    slice_3_index += 6 * unsigned(last == 4);
    return slice_1_index + 24 * slice_2_index + 24 * 24 * slice_3_index;
}

unsigned pruning::cornersOrientationToIndex(const unsigned orientation[]) {
    unsigned index = 0;
    for (int i = 0; i < 7; ++i) {
        index = index * 3 + orientation[i];
    }
    return index;
}

unsigned pruning::edgesOrientationToIndex(const unsigned orientation[]) {
    unsigned index = 0;
    for (int i = 0; i < 11; ++i) {
        index = index * 2 + orientation[i];
    }
    return index;
}

unsigned pruning::cornersPermutationToIndex(const unsigned permutation[]) {
    return lehmerCodeEncode(permutation, 8);
}

unsigned pruning::edgesPermutationToIndex(const unsigned permutation[]) {
    return lehmerCodeEncode(permutation, 12);
}

void pruning::indexToCornerOrientation(unsigned index, unsigned orientation[]) {
    int s = 0;
    for (int i = 6; i >= 0; --i) {
        orientation[i] = index % 3;
        index = (index - orientation[i]) / 3;
        s -= orientation[i];
        if (s < 0) {
            s += 3;
        }
    }
    orientation[7] = s;
}

void pruning::indexToEdgeOrientation(unsigned index, unsigned orientation[]) {
    int s = 0;
    for (int i = 10; i >= 0; --i) {
        orientation[i] = index % 2;
        index = (index - orientation[i]) / 2;
        s -= orientation[i];
        if (s < 0) {
            s += 2;
        }
    }
    orientation[11] = s;
}

void pruning::indexToCornerPermutation(unsigned index, unsigned permutation[]) {
    lehmerCodeDecode(index, permutation, 8);
}

void pruning::indexToEdgePermutation(unsigned index, unsigned permutation[]) {
    lehmerCodeDecode(index, permutation, 12);
}