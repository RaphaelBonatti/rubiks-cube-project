#include "computationalrepresentation.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::ElementsAre;
using testing::Test;

TEST(ExceptionTest, testImpossibleCombinationThrowsException) {
  char flat_cube[48] = {
      'L', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'U', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  EXPECT_THAT(
      [&]() -> void { ComputationalRepresentation comp_rep(flat_cube); },
      testing::ThrowsMessage<std::invalid_argument>(
          "Corner cubie 'BLL' does not exist!"));
}

TEST(VerificationTest, testInvalidCombinationCheckIsFalse) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'R', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_FALSE(comp_rep.checkCombination());
}

TEST(VerificationTest, testValidCombinationCheckIsTrue) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
}

TEST(CombinationTest, testIdentityIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testUIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'F', 'F', 'F', 'L',
      'L', 'L', 'L', 'L', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F',
      'B', 'B', 'B', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(4, 1, 2, 3, 5, 6, 7, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(4, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testDIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'B', 'B', 'B', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L',
      'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'B', 'B', 'B', 'B',
      'B', 'R', 'R', 'R', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(1, 2, 3, 4, 6, 7, 8, 5));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 9));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testFIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'D', 'L',
      'D', 'L', 'L', 'D', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'U', 'R', 'R', 'U', 'R', 'U', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'R', 'R', 'R', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(1, 2, 4, 8, 5, 6, 3, 7));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 0, 2, 1, 0, 0, 1, 2));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 2, 8, 4, 5, 6, 3, 11, 9, 10, 7, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testBIsCorrect) {
  char flat_cube[48] = {
      'R', 'R', 'R', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'U',
      'L', 'U', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'D', 'R', 'D', 'R', 'R', 'D', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'L', 'L', 'L',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(2, 6, 3, 4, 1, 5, 7, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(2, 1, 0, 0, 1, 2, 0, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(6, 2, 3, 4, 1, 9, 7, 8, 5, 10, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testRIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'F', 'U', 'F', 'U', 'U', 'F', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'D', 'F', 'D', 'F', 'F', 'D',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'U', 'B', 'B', 'U',
      'B', 'U', 'B', 'B', 'D', 'D', 'B', 'D', 'B', 'D', 'D', 'B',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(1, 3, 7, 4, 5, 2, 6, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(CombinationTest, testLIsCorrect) {
  char flat_cube[48] = {
      'B', 'U', 'U', 'B', 'U', 'B', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'U', 'F', 'F', 'U', 'F', 'U', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'D', 'B',
      'D', 'B', 'B', 'D', 'F', 'D', 'D', 'F', 'D', 'F', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(5, 2, 3, 1, 8, 6, 7, 4));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(1, 0, 0, 2, 2, 0, 0, 1));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 2, 3, 5, 12, 6, 7, 4, 9, 10, 11, 8));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1));
}

TEST(CombinationTest, testUInverseIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'B', 'B', 'B', 'L',
      'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F',
      'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(2, 3, 4, 1, 5, 6, 7, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(2, 3, 4, 1, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(CombinationTest, testRInverseIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'B', 'U', 'B', 'U', 'U', 'B', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'U', 'F', 'U', 'F', 'F', 'U',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'D', 'B', 'B', 'D',
      'B', 'D', 'B', 'B', 'D', 'D', 'F', 'D', 'F', 'D', 'D', 'F',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(1, 6, 2, 4, 5, 7, 3, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(1, 6, 3, 4, 5, 10, 2, 8, 9, 7, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(CombinationTest, testRUIsCorrect) {
  char flat_cube[48] = {
      'U', 'U', 'R', 'U', 'F', 'U', 'U', 'F', 'F', 'F', 'F', 'L',
      'L', 'L', 'L', 'L', 'R', 'R', 'D', 'F', 'D', 'F', 'F', 'D',
      'R', 'R', 'B', 'R', 'B', 'R', 'R', 'B', 'U', 'L', 'L', 'U',
      'B', 'U', 'B', 'B', 'D', 'D', 'B', 'D', 'B', 'D', 'D', 'L',
  };
  ComputationalRepresentation comp_rep(flat_cube);
  ASSERT_TRUE(comp_rep.checkCombination());
  ASSERT_THAT(comp_rep.corner_permutation, ElementsAre(4, 2, 7, 3, 5, 1, 6, 8));
  ASSERT_THAT(comp_rep.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(comp_rep.edge_permutation,
              ElementsAre(4, 7, 2, 3, 5, 1, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(comp_rep.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}
