#include "pruningtables.hpp"

#include <exception>
#include <map>
#include <set>

using pruning::Indexer;
using pruning::PhaseTable;
using std::map;
using std::queue;
using std::set;
using std::vector;

template <typename T>
void PhaseTable<T>::generateTable() {
    Cube cube{};
    indices = {};
    unsigned distance = 0;
    for (Indexer index : generateInitialStates()) {
        index.statify(cube);
        update(cube, distance);
    }
    ++distance;
    Indexer index = Indexer();
    uint change_distance_counter = indices.size();
    Indexer new_index = Indexer();
    while (!indices.empty()) {
        index = indices.front();
        for (int move : moves) {
            new_index = computeNextIndex(index, move);
            new_index.statify(cube);
            update(cube, distance);
        }
        indices.pop();
        --change_distance_counter;
        if (change_distance_counter == 0) {
            ++distance;
            change_distance_counter = indices.size();
        }
    }
}

template <typename T>
vector<Indexer> PhaseTable<T>::generateInitialStates() {
    return vector<Indexer>{Indexer()};
}

template <typename T>
void PhaseTable<T>::update(const Cube &cube, unsigned distance) {
    unsigned &value = getTableValue(cube);
    if (value == UINT32_MAX) {
        value = distance;
        indices.push(Indexer(cube));
    }
}

template <typename T>
Indexer PhaseTable<T>::computeNextIndex(Indexer &index, unsigned move) {
    Cube cube = Cube();
    index.statify(cube);
    cube.rotate(move);
    return Indexer(cube);
}

template class pruning::PhaseRunner<pruning::PhaseOneTable>;
template class pruning::PhaseRunner<pruning::PhaseTwoTable>;
template class pruning::PhaseRunner<pruning::PhaseThreeTable>;
template class pruning::PhaseRunner<pruning::PhaseFourTable>;

template <typename T>
pruning::PhaseRunner<T>::PhaseRunner(T &phase_table) : phase_table(phase_table) {}

template <typename T>
vector<unsigned> pruning::PhaseRunner<T>::run(Cube &cube) {
    vector<unsigned> solution{};
    while (getDistance(cube) > 0) {
        solution.push_back(findBestNextMove(cube));
        cube.rotate(solution.back());
    }
    return solution;
}

template <typename T>
unsigned pruning::PhaseRunner<T>::findBestNextMove(const Cube &cube) {
    Cube temp_cube = cube;
    unsigned current_distance = getDistance(cube);
    for (unsigned move : phase_table.moves) {
        temp_cube = cube;
        temp_cube.rotate(move);
        if (getDistance(temp_cube) < current_distance) {
            return move;
        }
    }
    throw std::logic_error(
        "There was no 'best move'! This can be due to an wrong table value.");
}

template <typename T>
unsigned pruning::PhaseRunner<T>::getDistance(const Cube &cube) {
    return phase_table.getTableValue(cube);
}

pruning::PhaseOneTable::PhaseOneTable() {
    moves = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    table = vector<unsigned>(2048, UINT32_MAX);
    generateTable();
}

unsigned &pruning::PhaseOneTable::getTableValue(const Cube &cube) {
    return table[Indexer(cube).edge_orientation_index];
}

pruning::PhaseTwoTable::PhaseTwoTable() {
    moves = {0, 1, 2, 3, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    table = vector<vector<unsigned>>(2187, vector<unsigned>(495, UINT32_MAX));
    generateTable();
}

unsigned &pruning::PhaseTwoTable::getTableValue(const Cube &cube) {
    return table[Indexer(cube).corner_orientation_index]
                [udEdgesPermutationToIndex(cube.edge_permutation)];
}

pruning::PhaseThreeTable::PhaseThreeTable() {
    moves = {0, 1, 6, 7, 8, 9, 10, 11, 12, 13};
    table = vector<vector<unsigned>>(40320, vector<unsigned>(70, UINT32_MAX));
    generateTable();
}

unsigned &pruning::PhaseThreeTable::getTableValue(const Cube &cube) {
    return table[Indexer(cube).corner_permutation_index]
                [lrEdgesPermutationToIndex(cube.edge_permutation)];
}

vector<Indexer> pruning::PhaseThreeTable::generateInitialStates() {
    vector<unsigned> moves = {6, 7, 8, 9, 10, 11};
    set<unsigned> visited{};
    vector<Indexer> indices{};
    Indexer index{};
    queue<Indexer> temp_indices{};
    temp_indices.push(index);
    Indexer new_index{};
    while (visited.size() < 96) {
        index = temp_indices.front();
        for (unsigned move : moves) {
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

pruning::PhaseFourTable::PhaseFourTable() {
    moves = {6, 7, 8, 9, 10, 11};
    table = vector<vector<unsigned>>(96, vector<unsigned>(6912, UINT32_MAX));
    generateTable();
}

unsigned &pruning::PhaseFourTable::getTableValue(const Cube &cube) {
    return table[tetradsPermutationToIndex(cube.corner_permutation)]
                [slicesPermutationToIndex(cube.edge_permutation)];
}
