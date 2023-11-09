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

template <typename T> class PhaseTable {
public:
  T table;
  std::vector<unsigned> moves;
  virtual unsigned &getTableValue(const Cube &cube) = 0;

protected:
  std::queue<Indexer> indices;
  void generateTable();
  virtual std::vector<Indexer> generateInitialStates();
  void update(const Cube &cube, unsigned distance);
  Indexer computeNextIndex(Indexer &index, unsigned move);
};

template <typename T> class PhaseRunner {
public:
  PhaseRunner(T &phase_table);
  std::vector<unsigned> run(Cube &cube);

private:
  T phase_table;
  std::vector<unsigned> solution;

  unsigned findBestNextMove(const Cube &cube);
  unsigned getDistance(const Cube &cube);
};

class PhaseOneTable : public PhaseTable<std::vector<unsigned>> {
public:
  PhaseOneTable();
  unsigned &getTableValue(const Cube &cube);
};

class PhaseTwoTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
public:
  PhaseTwoTable();
  unsigned &getTableValue(const Cube &cube);
};

class PhaseThreeTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
public:
  PhaseThreeTable();
  unsigned &getTableValue(const Cube &cube);
  std::vector<Indexer> generateInitialStates();
};

class PhaseFourTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
public:
  PhaseFourTable();
  unsigned &getTableValue(const Cube &cube);
};

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