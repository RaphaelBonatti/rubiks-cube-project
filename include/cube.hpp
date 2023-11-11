#ifndef COMPUTATIONAL_REPRESENTATION
#define COMPUTATIONAL_REPRESENTATION

class Cube {
   public:
    unsigned corner_permutation[8] = {0};
    unsigned corner_orientation[8] = {0};
    unsigned edge_permutation[12] = {0};
    unsigned edge_orientation[12] = {0};

    Cube();
    Cube(char flat_cube[]);
    bool checkCombination();
    void rotate(unsigned rotation_id);

   private:
    void computeCornerPermutationAndOrientation(char flat_cube[]);
    void computeEdgePermutationAndOrientation(char flat_cube[]);
    bool checkCubies();
    bool checkPermutations();
    bool checkOrientations();
    void rotateEdges(unsigned rotation_id);
    void rotateCorners(unsigned rotation_id);
};

#endif