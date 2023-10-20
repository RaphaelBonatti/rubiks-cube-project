#include "converter.hpp"
#include <algorithm>
#include <iostream>

using std::cout;
using std::sort;

int Representation::corners_facets[8][3] = {
    {1, 9, 35},   {3, 33, 27},  {8, 25, 19},  {6, 17, 11},
    {46, 40, 14}, {48, 32, 38}, {43, 24, 30}, {41, 16, 22}};
int Representation::edges_facets[12][2] = {
    {2, 34},  {5, 26},  {7, 18},  {4, 10},  {12, 37}, {29, 36},
    {28, 21}, {13, 20}, {47, 39}, {45, 31}, {42, 23}, {44, 15}};

map<string, int> Representation::sorted_colors_to_corner_id = {
    {"BLU", 1}, {"FLU", 4}, {"FRU", 3}, {"BRU", 2},
    {"DFL", 8}, {"DFR", 7}, {"BDR", 6}, {"BDL", 5},
};

map<string, int> Representation::sorted_colors_to_edge_id = {
    {"LU", 4},  {"FU", 3}, {"RU", 2}, {"BU", 1}, {"DL", 12}, {"DF", 11},
    {"DR", 10}, {"BD", 9}, {"FL", 8}, {"FR", 7}, {"BL", 5},  {"BR", 6},
};

map<char, int> Representation::corner_color_to_orientation[8] = {
    {{'U', 0}, {'L', 1}, {'B', 2}}, {{'U', 0}, {'B', 1}, {'R', 2}},
    {{'U', 0}, {'R', 1}, {'F', 2}}, {{'U', 0}, {'F', 1}, {'L', 2}},
    {{'D', 0}, {'B', 1}, {'L', 2}}, {{'D', 0}, {'R', 1}, {'B', 2}},
    {{'D', 0}, {'F', 1}, {'R', 2}}, {{'D', 0}, {'L', 1}, {'F', 2}}};

map<char, int> Representation::edge_color_to_orientation[12] = {
    {{'U', 0}, {'B', 1}}, {{'U', 0}, {'R', 1}}, {{'U', 0}, {'F', 1}},
    {{'U', 0}, {'L', 1}}, {{'B', 1}, {'L', 0}}, {{'B', 1}, {'R', 0}},
    {{'F', 1}, {'R', 0}}, {{'F', 1}, {'L', 0}}, {{'D', 0}, {'B', 1}},
    {{'D', 0}, {'R', 1}}, {{'D', 0}, {'F', 1}}, {{'D', 0}, {'L', 1}}};

string Representation::corner_facets_to_colors(int corner_id,
                                               char flat_cube[]) {
  const int *facets = Representation::corners_facets[corner_id];
  string colors;
  colors += flat_cube[facets[0] - 1];
  colors += flat_cube[facets[1] - 1];
  colors += flat_cube[facets[2] - 1];
  return colors;
}

string Representation::edge_facets_to_colors(int edge_id, char flat_cube[]) {
  const int *facets = Representation::edges_facets[edge_id];
  string colors;
  colors += flat_cube[facets[0] - 1];
  colors += flat_cube[facets[1] - 1];
  return colors;
}

void compute_corner_permutation_and_orientation(
    NumericalRepresentation &num_rep, char flat_cube[]) {
  for (int i = 0; i < 8; ++i) {
    string corner_colors =
        Representation::corner_facets_to_colors(i, flat_cube);
    string sorted_colors = corner_colors;
    sort(sorted_colors.begin(), sorted_colors.end());
    int corner_id = Representation::sorted_colors_to_corner_id[sorted_colors];
    num_rep.corner_permutation[i] = corner_id;
    char primary_facet_color = corner_colors[0];
    num_rep.corner_orientation[corner_id - 1] =
        Representation::corner_color_to_orientation[corner_id - 1]
                                                   [primary_facet_color];
  }
}

void compute_edge_permutation_and_orientation(NumericalRepresentation &num_rep,
                                              char flat_cube[]) {
  for (int i = 0; i < 12; ++i) {
    string edge_colors = Representation::edge_facets_to_colors(i, flat_cube);
    string sorted_colors = edge_colors;
    sort(sorted_colors.begin(), sorted_colors.end());
    int edge_id = Representation::sorted_colors_to_edge_id[sorted_colors];
    num_rep.edge_permutation[i] = edge_id;
    char primary_facet_color = edge_colors[0];
    num_rep.edge_orientation[edge_id - 1] =
        Representation::edge_color_to_orientation[edge_id - 1]
                                                 [primary_facet_color];
  }
}

bool check_combination(NumericalRepresentation &num_rep) {
  int count_corner_inversions = 0;
  for (int i = 0; i < 7; ++i) {
    for (int j = i; j < 8; ++j) {
      count_corner_inversions +=
          int(num_rep.corner_permutation[i] > num_rep.corner_permutation[j]);
    }
  }
  int count_edge_inversions = 0;
  for (int i = 0; i < 11; ++i) {
    for (int j = i; j < 12; ++j) {
      count_edge_inversions +=
          int(num_rep.edge_permutation[i] > num_rep.edge_permutation[j]);
    }
  }
  if (count_corner_inversions % 2 != count_edge_inversions % 2) {
    return false;
  }
  int sum_corner_orientations = 0;
  for (int i = 0; i < 8; ++i) {
    sum_corner_orientations += num_rep.corner_orientation[i];
  }
  if (sum_corner_orientations % 3 != 0) {
    return false;
  }
  int sum_edge_orientations = 0;
  for (int i = 0; i < 12; ++i) {
    sum_edge_orientations += num_rep.edge_orientation[i];
  }
  if (sum_edge_orientations % 2 != 0) {
    return false;
  }
  return true;
}
