#include "computational_representation.hpp"
#include <map>
#include <string>

using std::map;
using std::string;

// U=0 D=1 F=2 B=3 R=4 L=5
int corner_rotation_permutations[6][4] = {
    {1, 2, 3, 4}, {5, 8, 7, 6}, {3, 7, 8, 4},
    {1, 5, 6, 2}, {2, 6, 7, 3}, {1, 4, 8, 5},
};

int edge_rotation_permutations[6][4] = {{1, 2, 3, 4},  {9, 12, 11, 10},
                                        {3, 7, 11, 8}, {1, 5, 9, 6},
                                        {2, 6, 10, 7}, {4, 8, 12, 5}};

int corner_rotation_orientations[6][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 2, 0, 0, 2, 1}, {1, 2, 0, 0, 2, 1, 0, 0},
    {0, 1, 2, 0, 0, 2, 1, 0}, {2, 0, 0, 1, 1, 0, 0, 2},
};

int edge_rotation_orientations[6][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1}};

void ComputationalRepresentation::rotate(int rotation_id) {
  for (int i = 0; i < 8; ++i) {
    corner_orientation[corner_permutation[i] - 1] =
        (corner_orientation[corner_permutation[i] - 1] +
         corner_rotation_orientations[rotation_id][i]) %
        3;
  }

  for (int i = 0; i < 12; ++i) {
    edge_orientation[edge_permutation[i] - 1] =
        (edge_orientation[edge_permutation[i] - 1] +
         edge_rotation_orientations[rotation_id][i]) %
        2;
  }

  int index = corner_rotation_permutations[rotation_id][0] - 1;
  int temp1 = corner_permutation[index];
  int temp2 = 0;
  for (int i = 0; i < 4; ++i) {
    index = corner_rotation_permutations[rotation_id][(i + 1) % 4] - 1;
    temp2 = corner_permutation[index];
    corner_permutation[index] = temp1;
    temp1 = temp2;
  }

  index = edge_rotation_permutations[rotation_id][0] - 1;
  temp1 = edge_permutation[index];
  temp2 = 0;
  for (int i = 0; i < 4; ++i) {
    index = edge_rotation_permutations[rotation_id][(i + 1) % 4] - 1;
    temp2 = edge_permutation[index];
    edge_permutation[index] = temp1;
    temp1 = temp2;
  }
}