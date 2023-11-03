#include "pruningtables.hpp"
#include <array>
#include <exception>
#include <iterator>

using std::array;
using std::function;
using std::map;
using std::queue;
using std::set;
using std::vector;

pruning::Indexer::Indexer()
    : edge_orientation_index(0), edge_permutation_index(0),
      corner_orientation_index(0), corner_permutation_index(0){};

void pruning::Indexer::indexifyEdges(ComputationalRepresentation &comp_rep) {
  edge_orientation_index = edgesOrientationToIndex(comp_rep.edge_orientation);
  edge_permutation_index = edgesPermutationToIndex(comp_rep.edge_permutation);
}

void pruning::Indexer::indexifyCorners(ComputationalRepresentation &comp_rep) {
  corner_orientation_index =
      cornersOrientationToIndex(comp_rep.corner_orientation);
  corner_permutation_index =
      cornersPermutationToIndex(comp_rep.corner_permutation);
}

void pruning::Indexer::statifyEdges(ComputationalRepresentation &comp_rep) {
  indexToEdgeOrientation(edge_orientation_index, comp_rep.edge_orientation);
  indexToEdgePermutation(edge_permutation_index, comp_rep.edge_permutation);
}

void pruning::Indexer::statifyCorners(ComputationalRepresentation &comp_rep) {
  indexToCornerOrientation(corner_orientation_index,
                           comp_rep.corner_orientation);
  indexToCornerPermutation(corner_permutation_index,
                           comp_rep.corner_permutation);
}

template <typename T>
void pruning::generateTable(
    vector<unsigned> moves, T &table,
    function<void(Indexer &, unsigned, queue<Indexer> &, T &)> update,
    function<Indexer(Indexer &, unsigned)> computeNextIndex,
    function<vector<Indexer>()> generateInitialStates) {
  queue<Indexer> indices;
  unsigned distance = 0;
  for (Indexer index : generateInitialStates()) {
    update(index, distance, indices, table);
  }
  ++distance;
  Indexer index;
  uint change_distance_counter = indices.size();
  Indexer new_index;
  while (!indices.empty()) {
    index = indices.front();
    for (int move : moves) {
      new_index = computeNextIndex(index, move);
      update(new_index, distance, indices, table);
    }
    indices.pop();
    --change_distance_counter;
    if (change_distance_counter == 0) {
      ++distance;
      change_distance_counter = indices.size();
    }
  }
}

// Phase One --------------------------------------------

void pruning::PhaseOneTableGenerator::update(Indexer &index, unsigned distance,
                                             queue<Indexer> &indices,
                                             vector<unsigned> &table) {
  if (table[index.edge_orientation_index] == UINT32_MAX) {
    table[index.edge_orientation_index] = distance;
    indices.push(index);
  }
}

pruning::Indexer
pruning::PhaseOneTableGenerator::computeNextIndex(Indexer &index,
                                                  unsigned move) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  for (int i = 0; i < move / 6 + 1; ++i) {
    comp_rep.rotateEdges(move % 6);
  }
  Indexer new_index;
  new_index.indexifyEdges(comp_rep);
  return new_index;
}

vector<unsigned> pruning::PhaseOneTableGenerator::generate() {
  vector<unsigned> moves = {0, 1,  2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16, 17};
  vector<unsigned> table(2048, UINT32_MAX);
  generateTable<vector<unsigned>>(moves, table, update, computeNextIndex,
                                  []() { return vector<Indexer>{Indexer()}; });
  return table;
}

// Phase Two --------------------------------------------

void pruning::PhaseTwoTableGenerator::update(Indexer &index, unsigned distance,
                                             queue<Indexer> &indices,
                                             vector<vector<unsigned>> &table) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  index.statifyCorners(comp_rep);
  unsigned ud_perm_index = udEdgesPermutationToIndex(comp_rep.edge_permutation);
  if (table[index.corner_orientation_index][ud_perm_index] == UINT32_MAX) {
    table[index.corner_orientation_index][ud_perm_index] = distance;
    indices.push(index);
  }
}

pruning::Indexer
pruning::PhaseTwoTableGenerator::computeNextIndex(Indexer &index,
                                                  unsigned move) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  index.statifyCorners(comp_rep);
  for (int i = 0; i < move / 6 + 1; ++i) {
    comp_rep.rotate(move % 6);
  }
  Indexer new_index;
  new_index.indexifyEdges(comp_rep);
  new_index.indexifyCorners(comp_rep);
  return new_index;
}

vector<vector<unsigned>> pruning::PhaseTwoTableGenerator::generate() {
  vector<unsigned> moves = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  vector<vector<unsigned>> table(2187, vector<unsigned>(495, UINT32_MAX));
  generateTable<vector<vector<unsigned>>>(
      moves, table, update, computeNextIndex,
      []() { return vector<Indexer>{Indexer()}; });
  return table;
}

// Phase Three --------------------------------------------

void pruning::PhaseThreeTableGenerator::update(
    Indexer &index, unsigned distance, queue<Indexer> &indices,
    vector<vector<unsigned>> &table) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  index.statifyCorners(comp_rep);
  unsigned lr_perm_index = lrEdgesPermutationToIndex(comp_rep.edge_permutation);
  if (table[index.corner_permutation_index][lr_perm_index] == UINT32_MAX) {
    table[index.corner_permutation_index][lr_perm_index] = distance;
    indices.push(index);
  }
}

pruning::Indexer
pruning::PhaseThreeTableGenerator::computeNextIndex(Indexer &index,
                                                    unsigned move) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  index.statifyCorners(comp_rep);
  for (int i = 0; i < move / 6 + 1; ++i) {
    comp_rep.rotate(move % 6);
  }
  Indexer new_index;
  new_index.indexifyEdges(comp_rep);
  new_index.indexifyCorners(comp_rep);
  return new_index;
}

vector<pruning::Indexer>
pruning::PhaseThreeTableGenerator::generateInitialStates() {
  vector<unsigned> moves = {6, 7, 8, 9, 10, 11};
  set<unsigned> visited;
  vector<Indexer> indices;
  Indexer index;
  queue<Indexer> temp_indices;
  Indexer new_index;
  std::pair<std::set<unsigned int>::iterator, bool> ret;
  while (visited.size() < 96) {
    index = temp_indices.front();
    for (int move : moves) {
      new_index = computeNextIndex(index, move);
      if (visited.insert(new_index.corner_permutation_index).second) {
        temp_indices.push(new_index);
        indices.push_back(new_index);
      }
    }
    temp_indices.pop();
  }
  return indices;
}

vector<vector<unsigned>> pruning::PhaseThreeTableGenerator::generate() {
  vector<unsigned> moves = {0, 1, 6, 7, 8, 9, 10, 11, 12, 13};
  vector<vector<unsigned>> table(40320, vector<unsigned>(70, UINT32_MAX));
  generateTable<vector<vector<unsigned>>>(
      moves, table, update, computeNextIndex, generateInitialStates);
  return table;
}

// Phase Four --------------------------------------------

// Utils --------------------------------------------

unsigned nChooseK(unsigned n, unsigned k) {
  if (k > n)
    return 0;
  if (k * 2 > n)
    k = n - k;
  if (k == 0)
    return 1;

  int result = n;
  for (int i = 2; i <= k; ++i) {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}

unsigned pruning::udEdgesPermutationToIndex(int permutation[]) {
  unsigned index = 0;
  unsigned r = 4;
  for (int i = 11; i >= 0; --i) {
    if ((permutation[i] - 1) / 4 == 1) {
      index += nChooseK(i, r);
      --r;
    }
  }
  return index;
}

unsigned pruning::lrEdgesPermutationToIndex(int permutation[]) {
  unsigned mask[8] = {0, 1, 2, 3, 8, 9, 10, 11};
  unsigned index = 0;
  unsigned r = 4;
  unsigned cubie_id = 0;
  for (int i = 7; i >= 0; --i) {
    if ((permutation[mask[i]] - 1) % 2 == 0) {
      index += nChooseK(i, r);
      --r;
    }
  }
  return index;
}

int pruning::cornersOrientationToIndex(int orientation[]) {
  int index = 0;
  for (int i = 0; i < 7; ++i) {
    index = index * 3 + orientation[i];
  }
  return index;
}

int pruning::edgesOrientationToIndex(int orientation[]) {
  int index = 0;
  for (int i = 0; i < 11; ++i) {
    index = index * 2 + orientation[i];
  }
  return index;
}

unsigned pruning::lehmerCodeEncode(const int permutation[], unsigned size) {
  unsigned result = 0;
  for (int i = 0; i < size - 1; ++i) {
    for (int j = i + 1; j < size; ++j) {
      result = result + int(permutation[i] > permutation[j]);
    }
    result *= size - 1 - i;
  }
  return result;
}

int pruning::cornersPermutationToIndex(int permutation[]) {
  return lehmerCodeEncode(permutation, 8);
}

int pruning::edgesPermutationToIndex(int permutation[]) {
  return lehmerCodeEncode(permutation, 12);
}

void pruning::indexToCornerOrientation(int index, int orientation[]) {
  int s = 0;
  for (int i = 6; i >= 0; --i) {
    orientation[i] = index % 3;
    index = (index - orientation[i]) / 3;
    s -= orientation[i];
    if (s < 0) {
      s += 3;
    }
  }
  orientation[7] = s;
}

void pruning::indexToEdgeOrientation(int index, int orientation[]) {
  int s = 0;
  for (int i = 10; i >= 0; --i) {
    orientation[i] = index % 2;
    index = (index - orientation[i]) / 2;
    s -= orientation[i];
    if (s < 0) {
      s += 2;
    }
  }
  orientation[11] = s;
}

void pruning::lehmerCodeDecode(int index, int permutation[], unsigned size) {
  permutation[size - 1] = 1;
  for (int i = size - 2; i >= 0; --i) {
    permutation[i] = 1 + (index % (size - i));
    index = (index - (index % (size - i))) / (size - i);
    for (int j = i + 1; j < size; ++j) {
      permutation[j] = permutation[j] + int(permutation[j] >= permutation[i]);
    }
  }
}

void pruning::indexToCornerPermutation(int index, int permutation[]) {
  lehmerCodeDecode(index, permutation, 8);
}

void pruning::indexToEdgePermutation(int index, int permutation[]) {
  lehmerCodeDecode(index, permutation, 12);
}