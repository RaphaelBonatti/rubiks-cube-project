#include "piecesmapping.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::map;
using std::string;

const int structure::corners_facets[8][3] = {
    {1, 9, 35},   {3, 33, 27},  {8, 25, 19},  {6, 17, 11},
    {46, 40, 14}, {48, 32, 38}, {43, 24, 30}, {41, 16, 22}};
const int structure::edges_facets[12][2] = {
    {2, 34},  {5, 26},  {7, 18},  {4, 10},  {12, 37}, {29, 36},
    {28, 21}, {13, 20}, {47, 39}, {45, 31}, {42, 23}, {44, 15}};

map<string, int> structure::sorted_colors_to_corner_id = {
    {"BLU", 1}, {"FLU", 4}, {"FRU", 3}, {"BRU", 2},
    {"DFL", 8}, {"DFR", 7}, {"BDR", 6}, {"BDL", 5},
};

map<string, int> structure::sorted_colors_to_edge_id = {
    {"LU", 4},  {"FU", 3}, {"RU", 2}, {"BU", 1}, {"DL", 12}, {"DF", 11},
    {"DR", 10}, {"BD", 9}, {"FL", 8}, {"FR", 7}, {"BL", 5},  {"BR", 6},
};

map<char, int> structure::corner_color_to_orientation[8] = {
    {{'U', 0}, {'L', 1}, {'B', 2}}, {{'U', 0}, {'B', 1}, {'R', 2}},
    {{'U', 0}, {'R', 1}, {'F', 2}}, {{'U', 0}, {'F', 1}, {'L', 2}},
    {{'D', 0}, {'B', 1}, {'L', 2}}, {{'D', 0}, {'R', 1}, {'B', 2}},
    {{'D', 0}, {'F', 1}, {'R', 2}}, {{'D', 0}, {'L', 1}, {'F', 2}}};

map<char, int> structure::edge_color_to_orientation[12] = {
    {{'U', 0}, {'B', 1}}, {{'U', 0}, {'R', 1}}, {{'U', 0}, {'F', 1}},
    {{'U', 0}, {'L', 1}}, {{'B', 1}, {'L', 0}}, {{'B', 1}, {'R', 0}},
    {{'F', 1}, {'R', 0}}, {{'F', 1}, {'L', 0}}, {{'D', 0}, {'B', 1}},
    {{'D', 0}, {'R', 1}}, {{'D', 0}, {'F', 1}}, {{'D', 0}, {'L', 1}}};

string structure::corner_facets_to_colors(int corner_id, char flat_cube[]) {
  const int *facets = corners_facets[corner_id];
  string colors;
  colors += flat_cube[facets[0] - 1];
  colors += flat_cube[facets[1] - 1];
  colors += flat_cube[facets[2] - 1];
  return colors;
}

string structure::edge_facets_to_colors(int edge_id, char flat_cube[]) {
  const int *facets = edges_facets[edge_id];
  string colors;
  colors += flat_cube[facets[0] - 1];
  colors += flat_cube[facets[1] - 1];
  return colors;
}