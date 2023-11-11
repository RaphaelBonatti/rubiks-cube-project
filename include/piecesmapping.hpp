#ifndef PIECES_MAPPING
#define PIECES_MAPPING

#include <map>
#include <string>

namespace structure {
extern const unsigned corners_facets[8][3];
extern const unsigned edges_facets[12][2];
extern std::map<std::string, unsigned> sorted_colors_to_corner_id;
extern std::map<std::string, unsigned> sorted_colors_to_edge_id;
extern std::map<char, unsigned> corner_color_to_orientation[8];
extern std::map<char, unsigned> edge_color_to_orientation[12];

std::string cornerFacetsToColors(unsigned corner_id, char flat_cube[]);
std::string edgeFacetsToColors(unsigned edge_id, char flat_cube[]);
};  // namespace structure

#endif