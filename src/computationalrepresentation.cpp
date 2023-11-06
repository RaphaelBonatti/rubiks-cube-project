#include "computationalrepresentation.hpp"
#include "facerotations.hpp"
#include "piecesmapping.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

using std::cout;
using std::map;
using std::sort;
using std::string;

void ComputationalRepresentation::computeCornerPermutationAndOrientation(
    char flat_cube[]) {

void Cube::computeCornerPermutationAndOrientation(char flat_cube[]) {
  for (int i = 0; i < 8; ++i) {
    string corner_colors = structure::corner_facets_to_colors(i, flat_cube);
    string sorted_colors = corner_colors;
    sort(sorted_colors.begin(), sorted_colors.end());
    if (structure::sorted_colors_to_corner_id.find(sorted_colors) ==
        structure::sorted_colors_to_corner_id.end()) {
      throw std::invalid_argument("Corner cubie '" + sorted_colors +
                                  "' does not exist!");
    }
    int corner_id = structure::sorted_colors_to_corner_id[sorted_colors];
    corner_permutation[i] = corner_id;
    char primary_facet_color = corner_colors[0];
    corner_orientation[i] =
        structure::corner_color_to_orientation[corner_id - 1]
                                              [primary_facet_color];
  }
}

void Cube::computeEdgePermutationAndOrientation(char flat_cube[]) {
    char flat_cube[]) {
  for (int i = 0; i < 12; ++i) {
    string edge_colors = structure::edge_facets_to_colors(i, flat_cube);
    string sorted_colors = edge_colors;
    sort(sorted_colors.begin(), sorted_colors.end());
    if (structure::sorted_colors_to_edge_id.find(sorted_colors) ==
        structure::sorted_colors_to_edge_id.end()) {
      throw std::invalid_argument("Edge cubie '" + sorted_colors +
                                  "' does not exist!");
    }
    int edge_id = structure::sorted_colors_to_edge_id[sorted_colors];
    edge_permutation[i] = edge_id;
    char primary_facet_color = edge_colors[0];
    edge_orientation[i] =
        structure::edge_color_to_orientation[edge_id - 1][primary_facet_color];
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
          int(corner_permutation[i] > corner_permutation[j]);
    }
  }
  int count_edge_inversions = 0;
  for (int i = 0; i < 11; ++i) {
    for (int j = i; j < 12; ++j) {
      count_edge_inversions += int(edge_permutation[i] > edge_permutation[j]);
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

void Cube::rotate(int rotation_id) {
  rotateCorners(rotation_id);
  rotateEdges(rotation_id);
}

void Cube::rotateEdges(int rotation_id) {
  unsigned iterations = rotation_id / 6 + 1;
  unsigned rotation = rotation_id % 6;
  unsigned temp_orientation[12] = {0};
  unsigned temp_permutation[12] = {0};
  for (int i = 0; i < iterations; ++i) {
    for (int i = 0; i < 12; ++i) {
      temp_orientation[i] =
          (edge_orientation[structure::edge_rotation_permutations[rotation][i] -
                            1] +
           structure::edge_rotation_orientations[rotation][i]) %
          2;
      temp_permutation[i] =
          edge_permutation[structure::edge_rotation_permutations[rotation][i] -
  int temp_edge_permutation[12];
  for (int i = 0; i < 12; ++i) {
    temp_edge_permutation[i] =
        edge_permutation[structure::edge_rotation_permutations[rotation_id][i] -
                           1];
    }
    std::copy(temp_orientation, temp_orientation + 12, edge_orientation);
    std::copy(temp_permutation, temp_permutation + 12, edge_permutation);
  }
}

void Cube::rotateCorners(int rotation_id) {
  unsigned iterations = rotation_id / 6 + 1;
  unsigned rotation = rotation_id % 6;
  unsigned temp_orientation[8] = {0};
  unsigned temp_permutation[8] = {0};
  for (int i = 0; i < iterations; ++i) {
    for (int i = 0; i < 8; ++i) {
      temp_orientation[i] =
          (corner_orientation
               [structure::corner_rotation_permutations[rotation][i] - 1] +
           structure::corner_rotation_orientations[rotation][i]) %
          3;
      temp_permutation[i] = corner_permutation
          [structure::corner_rotation_permutations[rotation][i] - 1];
    }
    std::copy(temp_orientation, temp_orientation + 8, corner_orientation);
    std::copy(temp_permutation, temp_permutation + 8, corner_permutation);
  for (int i = 0; i < 8; ++i) {
    temp_corner_permutation[i] = corner_permutation
        [structure::corner_rotation_permutations[rotation_id][i] - 1];
  }
  std::copy(temp_corner_permutation, temp_corner_permutation + 8,
            corner_permutation);
}

void ComputationalRepresentation::rotateInverse(int rotation_id) {
  rotate(rotation_id);
  rotate(rotation_id);
  rotate(rotation_id);
}