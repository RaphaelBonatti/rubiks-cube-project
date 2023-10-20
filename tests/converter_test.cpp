#include "../include/converter.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;
using testing::Test;

TEST(ConfigurationTest, Identity) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, U) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'F', 'F', 'F', 'L',
      'L', 'L', 'L', 'L', 'R', 'R', 'R', 'F', 'F', 'F', 'F', 'F',
      'B', 'B', 'B', 'R', 'R', 'R', 'R', 'R', 'L', 'L', 'L', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(4, 1, 2, 3, 5, 6, 7, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(4, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, UInverse) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'B', 'B', 'B', 'L',
      'L', 'L', 'L', 'L', 'L', 'L', 'L', 'F', 'F', 'F', 'F', 'F',
      'F', 'F', 'F', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(2, 3, 4, 1, 5, 6, 7, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(2, 3, 4, 1, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, R) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'F', 'U', 'F', 'U', 'U', 'F', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'D', 'F', 'D', 'F', 'F', 'D',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'U', 'B', 'B', 'U',
      'B', 'U', 'B', 'B', 'D', 'D', 'B', 'D', 'B', 'D', 'D', 'B',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(1, 3, 7, 4, 5, 2, 6, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 1, 2, 0, 0, 2, 1, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, RInverse) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'B', 'U', 'B', 'U', 'U', 'B', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'F', 'F', 'U', 'F', 'U', 'F', 'F', 'U',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'D', 'B', 'B', 'D',
      'B', 'D', 'B', 'B', 'D', 'D', 'F', 'D', 'F', 'D', 'D', 'F',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(1, 6, 2, 4, 5, 7, 3, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 1, 2, 0, 0, 2, 1, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 6, 3, 4, 5, 10, 2, 8, 9, 7, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, L) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'B', 'U', 'U', 'B', 'U', 'B', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'L', 'L', 'L', 'U', 'F', 'F', 'U', 'F', 'U', 'F', 'F',
      'R', 'R', 'R', 'R', 'R', 'R', 'R', 'R', 'B', 'B', 'D', 'B',
      'D', 'B', 'B', 'D', 'F', 'D', 'D', 'F', 'D', 'F', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(5, 2, 3, 1, 8, 6, 7, 4));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(2, 0, 0, 1, 1, 0, 0, 2));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 2, 3, 5, 12, 6, 7, 4, 9, 10, 11, 8));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, D) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L',
      'L', 'B', 'B', 'B', 'F', 'F', 'F', 'F', 'F', 'L', 'L', 'L',
      'R', 'R', 'R', 'R', 'R', 'F', 'F', 'F', 'B', 'B', 'B', 'B',
      'B', 'R', 'R', 'R', 'D', 'D', 'D', 'D', 'D', 'D', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(1, 2, 3, 4, 6, 7, 8, 5));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 9));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, F) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'U', 'U', 'U', 'L', 'L', 'L', 'L', 'L', 'D', 'L',
      'D', 'L', 'L', 'D', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'U', 'R', 'R', 'U', 'R', 'U', 'R', 'R', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'R', 'R', 'R', 'D', 'D', 'D', 'D', 'D',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(1, 2, 4, 8, 5, 6, 3, 7));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(0, 0, 1, 2, 0, 0, 2, 1));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(1, 2, 8, 4, 5, 6, 3, 11, 9, 10, 7, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, B) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'R', 'R', 'R', 'U', 'U', 'U', 'U', 'U', 'U', 'L', 'L', 'U',
      'L', 'U', 'L', 'L', 'F', 'F', 'F', 'F', 'F', 'F', 'F', 'F',
      'R', 'R', 'D', 'R', 'D', 'R', 'R', 'D', 'B', 'B', 'B', 'B',
      'B', 'B', 'B', 'B', 'D', 'D', 'D', 'D', 'D', 'L', 'L', 'L',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(2, 6, 3, 4, 1, 5, 7, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(1, 2, 0, 0, 2, 1, 0, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(6, 2, 3, 4, 1, 9, 7, 8, 5, 10, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}

TEST(ConfigurationTest, UR) {
  NumericalRepresentation num_rep = {};
  char flat_cube[48] = {
      'U', 'U', 'R', 'U', 'F', 'U', 'U', 'F', 'F', 'F', 'F', 'L',
      'L', 'L', 'L', 'L', 'R', 'R', 'D', 'F', 'D', 'F', 'F', 'D',
      'R', 'R', 'B', 'R', 'B', 'R', 'R', 'B', 'U', 'L', 'L', 'U',
      'B', 'U', 'B', 'B', 'D', 'D', 'B', 'D', 'B', 'D', 'D', 'L',
  };
  compute_corner_permutation_and_orientation(num_rep, flat_cube);
  compute_edge_permutation_and_orientation(num_rep, flat_cube);
  ASSERT_THAT(num_rep.corner_permutation, ElementsAre(4, 2, 7, 3, 5, 1, 6, 8));
  ASSERT_THAT(num_rep.corner_orientation, ElementsAre(1, 2, 0, 0, 0, 2, 1, 0));
  ASSERT_THAT(num_rep.edge_permutation,
              ElementsAre(4, 7, 2, 3, 5, 1, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(num_rep.edge_orientation,
              ElementsAre(1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
  ASSERT_TRUE(check_combination(num_rep));
}
