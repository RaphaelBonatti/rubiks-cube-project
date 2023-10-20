#ifndef CONVERTER
#define CONVERTER

#include <map>
#include <string>

using std::map;
using std::string;

struct NumericalRepresentation {
  int corner_permutation[8] = {0};
  int corner_orientation[8] = {0};
  int edge_permutation[12] = {0};
  int edge_orientation[12] = {0};
};

namespace Representation {
extern int corners_facets[8][3];
extern int edges_facets[12][2];
extern map<string, int> sorted_colors_to_corner_id;
extern map<string, int> sorted_colors_to_edge_id;
extern map<char, int> corner_color_to_orientation[8];
extern map<char, int> edge_color_to_orientation[12];

string corner_facets_to_colors(int corner_id, char flat_cube[]);
string edge_facets_to_colors(int edge_id, char flat_cube[]);
}; // namespace Representation

void compute_corner_permutation_and_orientation(
    NumericalRepresentation &num_rep, char flat_cube[]);
void compute_edge_permutation_and_orientation(NumericalRepresentation &num_rep,
                                              char flat_cube[]);

#endif