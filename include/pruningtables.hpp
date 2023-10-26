#ifndef PRUNING_TABLES
#define PRUNING_TABLES

#include "computationalrepresentation.hpp"
#include <map>
#include <set>
#include <vector>

namespace pruning {

struct Indexer {
  unsigned edge_orientation_index;
  unsigned edge_permutation_index;
  unsigned corner_orientation_index;
  unsigned corner_permutation_index;
  Indexer();
  void indexifyEdges(ComputationalRepresentation &comp_rep);
  void indexifyCorners(ComputationalRepresentation &comp_rep);
  void statifyEdges(ComputationalRepresentation &comp_rep);
  void statifyCorners(ComputationalRepresentation &comp_rep);
};

class TableGenerator {
public:
  static void generatePhaseOneTable();
  static unsigned g1_moves[18];
  static std::vector<unsigned> g1_table;

private:
  static ComputationalRepresentation comp_rep;
  static unsigned count_down;
  static std::map<unsigned, std::map<unsigned, bool>> visited;
  static std::vector<Indexer> temp_indices;
  static void populatePhaseOneTable(Indexer &index, unsigned distance);
  static void updateTable(Indexer &index, unsigned distance);
  static bool isVisited(Indexer &index);
  static void addVisited(Indexer &index);
  static Indexer computeNextIndex(Indexer &index, unsigned move);
};

int cornersOrientationToIndex(int orientation[]);
int edgesOrientationToIndex(int orientation[]);
int cornersPermutationToIndex(int orientation[]);
int edgesPermutationToIndex(int orientation[]);
void indexToCornerOrientation(int index, int orientation[]);
void indexToEdgeOrientation(int index, int orientation[]);
void indexToCornerPermutation(int index, int permutation[]);
void indexToEdgePermutation(int index, int permutation[]);
unsigned lehmerCodeEncode(const int permutation[], unsigned size);
void lehmerCodeDecode(int index, int permutation[], unsigned size);
} // namespace pruning

#endif