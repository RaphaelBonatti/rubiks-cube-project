#include "computationalrepresentation.hpp"
#include "solver.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::vector;
using testing::ElementsAre;

TEST(SolverTest, testSimpleCubeCanBeSolved) {
  Cube comp_rep;
  comp_rep.rotate(4);
  vector<unsigned> solution = solve(comp_rep);
  ASSERT_THAT(solution, ElementsAre(4, 10));
}

TEST(SolverTest, testComplexCubeCanBeSolved) {
  char arr[48] = {'R', 'L', 'R', 'D', 'L', 'D', 'L', 'L', 'U', 'B', 'R', 'L',
                  'U', 'L', 'B', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
                  'U', 'U', 'D', 'D', 'R', 'U', 'U', 'L', 'B', 'B', 'B', 'B',
                  'D', 'D', 'D', 'U', 'D', 'R', 'R', 'U', 'R', 'B', 'R', 'B'};
  Cube cube(arr);
  ASSERT_TRUE(cube.checkCombination());
  vector<unsigned> solution = solve(cube);
  ASSERT_THAT(solution,
              ElementsAre(3, 10, 3, 4, 11, 0, 8, 7, 2, 0, 7, 3, 0, 8, 12, 8, 6,
                          9, 10, 0, 11, 0, 11, 8, 6, 8, 6, 8, 10, 6, 9));
}