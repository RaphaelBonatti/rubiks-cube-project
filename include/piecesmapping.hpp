#ifndef PIECES_MAPPING
#define PIECES_MAPPING

#include <map>
#include <string>

namespace structure {
extern const int corners_facets[8][3];
extern const int edges_facets[12][2];
extern std::map<std::string, int> sorted_colors_to_corner_id;
extern std::map<std::string, int> sorted_colors_to_edge_id;
extern std::map<char, int> corner_color_to_orientation[8];
extern std::map<char, int> edge_color_to_orientation[12];

std::string corner_facets_to_colors(int corner_id, char flat_cube[]);
std::string edge_facets_to_colors(int edge_id, char flat_cube[]);
}; // namespace structure

#endif