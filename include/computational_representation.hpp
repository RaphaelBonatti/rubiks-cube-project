#ifndef COMPUTATIONAL_REPRESENTATION
#define COMPUTATIONAL_REPRESENTATION

class ComputationalRepresentation {
public:
  int corner_permutation[8] = {0};
  int corner_orientation[8] = {0};
  int edge_permutation[12] = {0};
  int edge_orientation[12] = {0};

  ComputationalRepresentation(char flat_cube[]);
  bool checkCombination();

private:
  void computeCornerPermutationAndOrientation(char flat_cube[]);
  void computeEdgePermutationAndOrientation(char flat_cube[]);
  bool checkCubies();
  bool checkPermutations();
  bool checkOrientations();
};

#endif