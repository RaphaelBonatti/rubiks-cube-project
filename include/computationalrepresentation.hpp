#ifndef COMPUTATIONAL_REPRESENTATION
#define COMPUTATIONAL_REPRESENTATION

class ComputationalRepresentation {
public:
  int corner_permutation[8] = {0};
  int corner_orientation[8] = {0};
  int edge_permutation[12] = {0};
  int edge_orientation[12] = {0};

  // The default constructor init the cube to home position.
  ComputationalRepresentation();
  // The second constructor init the cube to passed combination.
  ComputationalRepresentation(char flat_cube[]);
  bool checkCombination();
  void rotate(int rotation_id);
  void rotateEdges(int rotation_id);
  void rotateCorners(int rotation_id);
  void rotateInverse(int rotation_id);

private:
  void computeCornerPermutationAndOrientation(char flat_cube[]);
  void computeEdgePermutationAndOrientation(char flat_cube[]);
  bool checkCubies();
  bool checkPermutations();
  bool checkOrientations();
};

#endif