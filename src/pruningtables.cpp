#include "pruningtables.hpp"
#include <array>
#include <exception>
#include <iterator>

using std::array;
using std::map;
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

ComputationalRepresentation pruning::TableGenerator::comp_rep =
    ComputationalRepresentation();

unsigned pruning::TableGenerator::g1_moves[18] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

vector<unsigned> pruning::TableGenerator::g1_table =
    vector<unsigned>(2048, UINT32_MAX);

unsigned pruning::TableGenerator::count_down = 2048;

map<unsigned, map<unsigned, bool>> pruning::TableGenerator::visited;

vector<pruning::Indexer> pruning::TableGenerator::temp_indices;

bool pruning::TableGenerator::isVisited(Indexer &index) {
  return (visited.find(index.edge_orientation_index) != visited.end() &&
          visited[index.edge_orientation_index].find(
              index.edge_permutation_index) !=
              visited[index.edge_orientation_index].end());
}

void pruning::TableGenerator::addVisited(Indexer &index) {
  visited[index.edge_orientation_index][index.edge_permutation_index] = true;
}

void pruning::TableGenerator::updateTable(Indexer &index, unsigned distance) {
  if (g1_table[index.edge_orientation_index] == UINT32_MAX) {
    g1_table[index.edge_orientation_index] = distance;
    count_down--;
  }
}

pruning::Indexer pruning::TableGenerator::computeNextIndex(Indexer &index,
                                                           unsigned move) {
  ComputationalRepresentation comp_rep = ComputationalRepresentation();
  index.statifyEdges(comp_rep);
  comp_rep.rotate(move);
  Indexer new_index;
  new_index.indexifyEdges(comp_rep);
  return new_index;
}

void pruning::TableGenerator::generatePhaseOneTable() {
  Indexer index;
  updateTable(index, 0);
  vector<Indexer> indices = {index};
  addVisited(index);
  for (unsigned distance = 1; distance < 8; ++distance) {
    for (Indexer index : indices) {
      populatePhaseOneTable(index, distance);
      if (count_down == 0) {
        return;
      }
    }
    indices = temp_indices;
    temp_indices.clear();
  }
}

void pruning::TableGenerator::populatePhaseOneTable(Indexer &index,
                                                    unsigned distance) {
  Indexer new_index;
  for (int move : g1_moves) {
    new_index = computeNextIndex(index, move);
    if (isVisited(new_index)) {
      continue;
    }
    updateTable(new_index, distance);
    temp_indices.emplace_back(new_index);
    addVisited(new_index);
  }
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