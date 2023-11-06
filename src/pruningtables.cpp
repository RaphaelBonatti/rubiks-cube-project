#include "pruningtables.hpp"
#include <algorithm>
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

pruning::Indexer::Indexer(const Cube &cube) { indexify(cube); }

void pruning::Indexer::indexify(const Cube &cube) {
  indexifyEdges(cube);
  indexifyCorners(cube);
}

void pruning::Indexer::statify(Cube &cube) {
  statifyEdges(cube);
  statifyCorners(cube);
}

void pruning::Indexer::indexifyEdges(const Cube &cube) {
  edge_orientation_index = edgesOrientationToIndex(cube.edge_orientation);
  edge_permutation_index = edgesPermutationToIndex(cube.edge_permutation);
}

void pruning::Indexer::indexifyCorners(const Cube &cube) {
  corner_orientation_index = cornersOrientationToIndex(cube.corner_orientation);
  corner_permutation_index = cornersPermutationToIndex(cube.corner_permutation);
}

void pruning::Indexer::statifyEdges(Cube &cube) {
  indexToEdgeOrientation(edge_orientation_index, cube.edge_orientation);
  indexToEdgePermutation(edge_permutation_index, cube.edge_permutation);
}

void pruning::Indexer::statifyCorners(Cube &cube) {
  indexToCornerOrientation(corner_orientation_index, cube.corner_orientation);
  indexToCornerPermutation(corner_permutation_index, cube.corner_permutation);
}

template <typename T>
void pruning::generateTable(
    vector<unsigned> moves, T &table,
    function<void(Indexer &, unsigned, queue<Indexer> &, T &)> update,
    function<vector<Indexer>()> generateInitialStates) {
  queue<Indexer> indices = {};
  unsigned distance = 0;
  for (Indexer index : generateInitialStates()) {
    update(index, distance, indices, table);
  }
  ++distance;
  Indexer index = Indexer();
  uint change_distance_counter = indices.size();
  Indexer new_index = Indexer();
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

vector<unsigned> pruning::PhaseOneTableGenerator::generate() {
  vector<unsigned> moves = {0, 1,  2,  3,  4,  5,  6,  7,  8,
                            9, 10, 11, 12, 13, 14, 15, 16, 17};
  vector<unsigned> table(2048, UINT32_MAX);
  generateTable<vector<unsigned>>(moves, table, update,
                                  []() { return vector<Indexer>{Indexer()}; });
  return table;
}

// Phase Two --------------------------------------------

void pruning::PhaseTwoTableGenerator::update(Indexer &index, unsigned distance,
                                             queue<Indexer> &indices,
                                             vector<vector<unsigned>> &table) {
  Cube cube = Cube();
  index.statify(cube);
  unsigned ud_perm_index = udEdgesPermutationToIndex(cube.edge_permutation);
  if (table[index.corner_orientation_index][ud_perm_index] == UINT32_MAX) {
    table[index.corner_orientation_index][ud_perm_index] = distance;
    indices.push(index);
  }
}

vector<vector<unsigned>> pruning::PhaseTwoTableGenerator::generate() {
  vector<unsigned> moves = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  vector<vector<unsigned>> table(2187, vector<unsigned>(495, UINT32_MAX));
  generateTable<vector<vector<unsigned>>>(
      moves, table, update, []() { return vector<Indexer>{Indexer()}; });
  return table;
}

// Phase Three --------------------------------------------

void pruning::PhaseThreeTableGenerator::update(
    Indexer &index, unsigned distance, queue<Indexer> &indices,
    vector<vector<unsigned>> &table) {
  Cube cube = Cube();
  index.statify(cube);
  unsigned lr_perm_index = lrEdgesPermutationToIndex(cube.edge_permutation);
  if (table[index.corner_permutation_index][lr_perm_index] == UINT32_MAX) {
    table[index.corner_permutation_index][lr_perm_index] = distance;
    indices.push(index);
  }
}

vector<pruning::Indexer>
pruning::PhaseThreeTableGenerator::generateInitialStates() {
  vector<unsigned> moves = {6, 7, 8, 9, 10, 11};
  set<unsigned> visited{};
  vector<Indexer> indices{};
  Indexer index{};
  queue<Indexer> temp_indices{};
  temp_indices.push(index);
  Indexer new_index{};
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
  generateTable<vector<vector<unsigned>>>(moves, table, update,
                                          generateInitialStates);
  return table;
}

// Phase Four --------------------------------------------

void pruning::PhaseFourTableGenerator::update(Indexer &index, unsigned distance,
                                              queue<Indexer> &indices,
                                              vector<vector<unsigned>> &table) {
  Cube cube = Cube();
  index.statify(cube);
  unsigned tetrads_index = tetradsPermutationToIndex(cube.corner_permutation);
  unsigned slices_index = slicesPermutationToIndex(cube.edge_permutation);

  if (table[tetrads_index][slices_index] == UINT32_MAX) {
    table[tetrads_index][slices_index] = distance;
    indices.push(index);
  }
}

vector<vector<unsigned>> pruning::PhaseFourTableGenerator::generate() {
  vector<unsigned> moves = {6, 7, 8, 9, 10, 11};
  vector<vector<unsigned>> table(96, vector<unsigned>(6912, UINT32_MAX));
  generateTable<vector<vector<unsigned>>>(
      moves, table, update, []() { return vector<Indexer>{Indexer()}; });
  return table;
}

// Utils --------------------------------------------

pruning::Indexer pruning::computeNextIndex(Indexer &index, unsigned move) {
  Cube cube = Cube();
  index.statify(cube);
  cube.rotate(move);
  return Indexer(cube);
}

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

unsigned pruning::udEdgesPermutationToIndex(const int permutation[]) {
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

unsigned pruning::lrEdgesPermutationToIndex(const int permutation[]) {
  unsigned mask[8] = {0, 1, 2, 3, 8, 9, 10, 11};
  unsigned index = 0;
  unsigned r = 4;
  for (int i = 7; i >= 0; --i) {
    if ((permutation[mask[i]] - 1) % 2 == 0) {
      index += nChooseK(i, r);
      --r;
    }
  }
  return index;
}

unsigned pruning::tetradsPermutationToIndex(const int permutation[]) {
  int tetrad_1[4] = {permutation[0], permutation[2], permutation[5],
                     permutation[7]};
  int tetrad_2[4] = {permutation[1], permutation[3], permutation[4],
                     permutation[6]};
  unsigned tetrad_1_permutation_index = lehmerCodeEncode(tetrad_1, 4);
  unsigned tetrad_2_position_index =
      std::find(tetrad_2, tetrad_2 + 4, 2) - tetrad_2;
  return tetrad_1_permutation_index + 24 * tetrad_2_position_index;
}

unsigned pruning::slicesPermutationToIndex(const int permutation[]) {
  int slice_1[4] = {permutation[0], permutation[2], permutation[8],
                    permutation[10]};
  int slice_2[4] = {permutation[4], permutation[5], permutation[6],
                    permutation[7]};
  int slice_3[4] = {permutation[1], permutation[3], permutation[9],
                    permutation[11]};
  unsigned slice_1_index = lehmerCodeEncode(slice_1, 4);
  unsigned slice_2_index = lehmerCodeEncode(slice_2, 4);
  unsigned slice_3_index = 0;
  unsigned r = 2;
  unsigned last = 0;
  for (int i = 3; i >= 0; --i) {
    if (slice_3[i] < 5) {
      slice_3_index += nChooseK(i, r);
      --r;
      last = slice_3[i];
    }
  }
  slice_3_index += 6 * int(last == 4);
  return slice_1_index + 24 * slice_2_index + 24 * 24 * slice_3_index;
}

int pruning::cornersOrientationToIndex(const int orientation[]) {
  int index = 0;
  for (int i = 0; i < 7; ++i) {
    index = index * 3 + orientation[i];
  }
  return index;
}

int pruning::edgesOrientationToIndex(const int orientation[]) {
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

int pruning::cornersPermutationToIndex(const int permutation[]) {
  return lehmerCodeEncode(permutation, 8);
}

int pruning::edgesPermutationToIndex(const int permutation[]) {
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