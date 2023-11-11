#include "cube.hpp"

#include <algorithm>
#include <stdexcept>

#include "piecesmapping.hpp"
#include "rotation.hpp"

using rotation::corner_orientations;
using rotation::corner_permutations;
using rotation::edge_orientations;
using rotation::edge_permutations;
using std::map;
using std::sort;
using std::string;
using structure::corner_color_to_orientation;
using structure::cornerFacetsToColors;
using structure::edge_color_to_orientation;
using structure::edgeFacetsToColors;
using structure::sorted_colors_to_corner_id;
using structure::sorted_colors_to_edge_id;

unsigned identifyCubie(string colors) {
    map<std::string, unsigned> sorted_colors_to_id;
    switch (colors.length()) {
        case 2:
            sorted_colors_to_id = sorted_colors_to_edge_id;
            break;
        case 3:
            sorted_colors_to_id = sorted_colors_to_corner_id;
            break;
        default:
            throw std::invalid_argument("Cubies must have 2 or 3 colors!");
    }

    sort(colors.begin(), colors.end());
    if (sorted_colors_to_id.find(colors) == sorted_colors_to_id.end()) {
        throw std::invalid_argument("Corner cubie '" + colors + "' does not exist!");
    }
    return sorted_colors_to_id[colors];
}

void Cube::computeCornerPermutationAndOrientation(char flat_cube[]) {
    for (int i = 0; i < 8; ++i) {
        string corner_colors = cornerFacetsToColors(i, flat_cube);
        unsigned corner_id = identifyCubie(corner_colors);
        corner_permutation[i] = corner_id;
        corner_orientation[i] = corner_color_to_orientation[corner_id - 1][corner_colors[0]];
    }
}

void Cube::computeEdgePermutationAndOrientation(char flat_cube[]) {
    for (int i = 0; i < 12; ++i) {
        string edge_colors = edgeFacetsToColors(i, flat_cube);
        unsigned edge_id = identifyCubie(edge_colors);
        edge_permutation[i] = edge_id;
        edge_orientation[i] = edge_color_to_orientation[edge_id - 1][edge_colors[0]];
    }
}

Cube::Cube() {
    for (int i = 0; i < 8; ++i) {
        corner_permutation[i] = i + 1;
    }
    for (int i = 0; i < 12; ++i) {
        edge_permutation[i] = i + 1;
    }
}

Cube::Cube(char flat_cube[]) {
    computeCornerPermutationAndOrientation(flat_cube);
    computeEdgePermutationAndOrientation(flat_cube);
}

bool Cube::checkCubies() {
    for (int i = 0; i < 8; ++i) {
        if (corner_permutation[i] == 0) {
            return false;
        }
    }
    for (int i = 0; i < 12; ++i) {
        if (edge_permutation[i] == 0) {
            return false;
        }
    }
    return true;
}

bool Cube::checkPermutations() {
    int count_corner_inversions = 0;
    for (int i = 0; i < 7; ++i) {
        for (int j = i; j < 8; ++j) {
            count_corner_inversions +=
                unsigned(corner_permutation[i] > corner_permutation[j]);
        }
    }
    int count_edge_inversions = 0;
    for (int i = 0; i < 11; ++i) {
        for (int j = i; j < 12; ++j) {
            count_edge_inversions += unsigned(edge_permutation[i] > edge_permutation[j]);
        }
    }
    if (count_corner_inversions % 2 != count_edge_inversions % 2) {
        return false;
    }
    return true;
}

bool Cube::checkOrientations() {
    int sum_corner_orientations = 0;
    for (int i = 0; i < 8; ++i) {
        sum_corner_orientations += corner_orientation[i];
    }
    if (sum_corner_orientations % 3 != 0) {
        return false;
    }
    int sum_edge_orientations = 0;
    for (int i = 0; i < 12; ++i) {
        sum_edge_orientations += edge_orientation[i];
    }
    if (sum_edge_orientations % 2 != 0) {
        return false;
    }
    return true;
}

bool Cube::checkCombination() {
    return checkCubies() && checkPermutations() && checkOrientations();
}

void Cube::rotate(unsigned rotation_id) {
    rotateCorners(rotation_id);
    rotateEdges(rotation_id);
}

void Cube::rotateEdges(unsigned rotation_id) {
    unsigned iterations = rotation_id / 6 + 1;
    unsigned rotation = rotation_id % 6;
    unsigned temp_orientation[12] = {0};
    unsigned temp_permutation[12] = {0};
    for (int i = 0; i < iterations; ++i) {
        for (int i = 0; i < 12; ++i) {
            temp_orientation[i] =
                (edge_orientation[rotation::edge_permutations[rotation][i] - 1] +
                 rotation::edge_orientations[rotation][i]) %
                2;
            temp_permutation[i] =
                edge_permutation[rotation::edge_permutations[rotation][i] - 1];
        }
        std::copy(temp_orientation, temp_orientation + 12, edge_orientation);
        std::copy(temp_permutation, temp_permutation + 12, edge_permutation);
    }
}

void Cube::rotateCorners(unsigned rotation_id) {
    unsigned iterations = rotation_id / 6 + 1;
    unsigned rotation = rotation_id % 6;
    unsigned temp_orientation[8] = {0};
    unsigned temp_permutation[8] = {0};
    for (int i = 0; i < iterations; ++i) {
        for (int i = 0; i < 8; ++i) {
            temp_orientation[i] =
                (corner_orientation[rotation::corner_permutations[rotation][i] - 1] +
                 rotation::corner_orientations[rotation][i]) %
                3;
            temp_permutation[i] =
                corner_permutation[rotation::corner_permutations[rotation][i] - 1];
        }
        std::copy(temp_orientation, temp_orientation + 8, corner_orientation);
        std::copy(temp_permutation, temp_permutation + 8, corner_permutation);
    }
}