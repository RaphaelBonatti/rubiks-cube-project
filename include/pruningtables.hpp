#ifndef PRUNING_TABLES
#define PRUNING_TABLES

#include "computationalrepresentation.hpp"
#include <functional>
#include <map>
#include <queue>
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
class PhaseOneTableGenerator {
public:
  static std::vector<unsigned> generate();
  static unsigned g1_moves[18];
  static std::vector<unsigned> g1_table;

private:
  static void update(Indexer &index, unsigned distance,
                     std::queue<Indexer> &indices,
                     std::vector<unsigned> &table);
  static Indexer computeNextIndex(Indexer &index, unsigned move);
};
  static void updateTable(Indexer &index, unsigned distance);
  static bool isVisited(Indexer &index);
  static void addVisited(Indexer &index);
  static Indexer computeNextIndex(Indexer &index, unsigned move);
};

template <typename T>
void generateTable(
    std::vector<unsigned> moves, T &table,
    std::function<void(Indexer &, unsigned, std::queue<Indexer> &, T &)> update,
    std::function<Indexer(Indexer &, unsigned)> computeNextIndex);
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