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
  Indexer(const Cube &comp_rep);
  void indexify(const Cube &comp_rep);
  void statify(Cube &comp_rep);
  void indexifyEdges(const Cube &comp_rep);
  void indexifyCorners(const Cube &comp_rep);
  void statifyEdges(Cube &comp_rep);
  void statifyCorners(Cube &comp_rep);
};

class PhaseOneTableGenerator {
public:
  static std::vector<unsigned> generate();

private:
  static void update(Indexer &index, unsigned distance,
                     std::queue<Indexer> &indices,
                     std::vector<unsigned> &table);
};

class PhaseTwoTableGenerator {
public:
  static std::vector<std::vector<unsigned>> generate();

private:
  static void update(Indexer &index, unsigned distance,
                     std::queue<Indexer> &indices,
                     std::vector<std::vector<unsigned>> &table);
};

class PhaseThreeTableGenerator {
public:
  static std::vector<std::vector<unsigned>> generate();

private:
  static void update(Indexer &index, unsigned distance,
                     std::queue<Indexer> &indices,
                     std::vector<std::vector<unsigned>> &table);
  static std::vector<Indexer> generateInitialStates();
};

class PhaseFourTableGenerator {
public:
  static std::vector<std::vector<unsigned>> generate();

private:
  static void update(Indexer &index, unsigned distance,
                     std::queue<Indexer> &indices,
                     std::vector<std::vector<unsigned>> &table);
};

template <typename T>
void generateTable(
    std::vector<unsigned> moves, T &table,
    std::function<void(Indexer &, unsigned, std::queue<Indexer> &, T &)> update,
    std::function<std::vector<Indexer>()> generateInitialStates);
Indexer computeNextIndex(Indexer &index, unsigned move);
unsigned udEdgesPermutationToIndex(const int permutation[]);
unsigned lrEdgesPermutationToIndex(const int permutation[]);
unsigned tetradsPermutationToIndex(const int permutation[]);
unsigned slicesPermutationToIndex(const int permutation[]);
int cornersOrientationToIndex(const int orientation[]);
int edgesOrientationToIndex(const int orientation[]);
int cornersPermutationToIndex(const int orientation[]);
int edgesPermutationToIndex(const int orientation[]);
void indexToCornerOrientation(int index, int orientation[]);
void indexToEdgeOrientation(int index, int orientation[]);
void indexToCornerPermutation(int index, int permutation[]);
void indexToEdgePermutation(int index, int permutation[]);
unsigned lehmerCodeEncode(const int permutation[], unsigned size);
void lehmerCodeDecode(int index, int permutation[], unsigned size);
} // namespace pruning

#endif