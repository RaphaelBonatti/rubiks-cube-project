#ifndef ROTATION
#define ROTATION

#include <string>

namespace rotation {
extern const char faces[6];
extern const unsigned corner_permutations[6][8];
extern const unsigned edge_permutations[6][12];
extern const unsigned corner_orientations[6][8];
extern const unsigned edge_orientations[6][12];
}  // namespace rotation

#endif
