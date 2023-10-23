#include "computationalrepresentation.hpp"
#include "facerotations.hpp"
#include "piecesmapping.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::cout;
using std::map;
using std::sort;
using std::string;

void ComputationalRepresentation::computeCornerPermutationAndOrientation(
    char flat_cube[]) {
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
    corner_orientation[corner_id - 1] =
        structure::corner_color_to_orientation[corner_id - 1]
                                              [primary_facet_color];
  }
}

void ComputationalRepresentation::computeEdgePermutationAndOrientation(
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
    edge_orientation[edge_id - 1] =
        structure::edge_color_to_orientation[edge_id - 1][primary_facet_color];
  }
}

ComputationalRepresentation::ComputationalRepresentation() {
  for (int i = 0; i < 8; ++i) {
    corner_permutation[i] = i + 1;
  }
  for (int i = 0; i < 12; ++i) {
    edge_permutation[i] = i + 1;
  }
}

ComputationalRepresentation::ComputationalRepresentation(char flat_cube[]) {
  computeCornerPermutationAndOrientation(flat_cube);
  computeEdgePermutationAndOrientation(flat_cube);
}

bool ComputationalRepresentation::checkCubies() {
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

bool ComputationalRepresentation::checkPermutations() {
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

bool ComputationalRepresentation::checkOrientations() {
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

bool ComputationalRepresentation::checkCombination() {
  return checkCubies() && checkPermutations() && checkOrientations();
}

void ComputationalRepresentation::rotate(int rotation_id) {
  for (int i = 0; i < 8; ++i) {
    corner_orientation[corner_permutation[i] - 1] =
        (corner_orientation[corner_permutation[i] - 1] +
         structure::corner_rotation_orientations[rotation_id][i]) %
        3;
  }

  for (int i = 0; i < 12; ++i) {
    edge_orientation[edge_permutation[i] - 1] =
        (edge_orientation[edge_permutation[i] - 1] +
         structure::edge_rotation_orientations[rotation_id][i]) %
        2;
  }

  int index = structure::corner_rotation_permutations[rotation_id][0] - 1;
  int temp1 = corner_permutation[index];
  int temp2 = 0;
  for (int i = 0; i < 4; ++i) {
    index =
        structure::corner_rotation_permutations[rotation_id][(i + 1) % 4] - 1;
    temp2 = corner_permutation[index];
    corner_permutation[index] = temp1;
    temp1 = temp2;
  }

  index = structure::edge_rotation_permutations[rotation_id][0] - 1;
  temp1 = edge_permutation[index];
  temp2 = 0;
  for (int i = 0; i < 4; ++i) {
    index = structure::edge_rotation_permutations[rotation_id][(i + 1) % 4] - 1;
    temp2 = edge_permutation[index];
    edge_permutation[index] = temp1;
    temp1 = temp2;
  }
}