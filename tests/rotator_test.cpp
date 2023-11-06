#include "computationalrepresentation.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;
using testing::Test;

TEST(RotationTest, testRotationUIsCorrect) {
  Cube cube;
  cube.rotate(0);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(4, 1, 2, 3, 5, 6, 7, 8));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(4, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(RotationTest, testRotationDIsCorrect) {
  Cube cube;
  cube.rotate(1);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(1, 2, 3, 4, 6, 7, 8, 5));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 0, 0, 0, 0, 0, 0, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 9));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(RotationTest, testRotationFIsCorrect) {
  Cube cube;
  cube.rotate(2);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(1, 2, 4, 8, 5, 6, 3, 7));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 0, 2, 1, 0, 0, 1, 2));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(1, 2, 8, 4, 5, 6, 3, 11, 9, 10, 7, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(RotationTest, testRotationBIsCorrect) {
  Cube cube;
  cube.rotate(3);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(2, 6, 3, 4, 1, 5, 7, 8));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(2, 1, 0, 0, 1, 2, 0, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(6, 2, 3, 4, 1, 9, 7, 8, 5, 10, 11, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(RotationTest, testRotationRIsCorrect) {
  Cube cube;
  cube.rotate(4);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(1, 3, 7, 4, 5, 2, 6, 8));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(RotationTest, testRotationLIsCorrect) {
  Cube cube;
  cube.rotate(5);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(5, 2, 3, 1, 8, 6, 7, 4));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(1, 0, 0, 2, 2, 0, 0, 1));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(1, 2, 3, 5, 12, 6, 7, 4, 9, 10, 11, 8));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1));
}

TEST(RotationTest, testRotationRUIsCorrect) {
  Cube cube;
  cube.rotate(0);
  cube.rotate(4);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(4, 2, 7, 3, 5, 1, 6, 8));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(4, 7, 2, 3, 5, 1, 10, 8, 9, 6, 11, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(RotationTest, testRotationFRUIsCorrect) {
  Cube cube;
  cube.rotate(0);
  cube.rotate(4);
  cube.rotate(2);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(4, 2, 3, 8, 5, 1, 7, 6));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 2, 2, 1, 0, 1, 2, 1));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(4, 7, 8, 3, 5, 1, 2, 11, 9, 6, 10, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0));
}

TEST(RotationTest, testRotationRInverseIsCorrect) {
  Cube cube;
  cube.rotate(16);
  ASSERT_THAT(cube.corner_permutation, ElementsAre(1, 6, 2, 4, 5, 7, 3, 8));
  ASSERT_THAT(cube.corner_orientation, ElementsAre(0, 2, 1, 0, 0, 1, 2, 0));
  ASSERT_THAT(cube.edge_permutation,
              ElementsAre(1, 6, 3, 4, 5, 10, 2, 8, 9, 7, 11, 12));
  ASSERT_THAT(cube.edge_orientation,
              ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}