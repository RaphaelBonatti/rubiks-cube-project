#ifndef COMPUTATIONAL_REPRESENTATION
#define COMPUTATIONAL_REPRESENTATION

class ComputationalRepresentation {
public:
  int corner_permutation[8] = {0};
  int corner_orientation[8] = {0};
  int edge_permutation[12] = {0};
  int edge_orientation[12] = {0};

  ComputationalRepresentation(char flat_cube[]);
  bool check_combination();

private:
  void compute_corner_permutation_and_orientation(char flat_cube[]);
  void compute_edge_permutation_and_orientation(char flat_cube[]);
  bool check_cubies();
  bool check_permutations();
  bool check_orientations();
};

#endif