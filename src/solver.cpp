#include "solver.hpp"

#include <exception>
#include <functional>
#include <iostream>

#include "pruningtables.hpp"
#include "utils.hpp"

using pruning::Indexer;
using pruning::PhaseFourTable;
using pruning::PhaseOneTable;
using pruning::PhaseRunner;
using pruning::PhaseTable;
using pruning::PhaseThreeTable;
using pruning::PhaseTwoTable;
using std::function;
using std::vector;

vector<unsigned> solve(Cube cube) {
    vector<unsigned> solution = {};
    PhaseOneTable phase_one_table{};
    PhaseRunner<PhaseOneTable> phase_one_runner(phase_one_table);
    extendVector(solution, phase_one_runner.run(cube));
    PhaseTwoTable phase_two_table{};
    PhaseRunner<PhaseTwoTable> phase_two_runner(phase_two_table);
    extendVector(solution, phase_two_runner.run(cube));
    PhaseThreeTable phase_three_table{};
    PhaseRunner<PhaseThreeTable> phase_three_runner(phase_three_table);
    extendVector(solution, phase_three_runner.run(cube));
    PhaseFourTable phase_four_table{};
    PhaseRunner<PhaseFourTable> phase_four_runner(phase_four_table);
    extendVector(solution, phase_four_runner.run(cube));
    return solution;
}