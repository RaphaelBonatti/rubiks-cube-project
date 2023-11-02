#include "pruningtables.hpp"
#include <algorithm>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>

using testing::ElementsAre;
using testing::Test;

TEST(IndexationTest, testCornersOrientationIdentityIsIndex0) {
  int orientation[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int index = pruning::cornersOrientationToIndex(orientation);
  ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testCornersOrientationRPositionIsIndex412) {
  int orientation[8] = {0, 1, 2, 0, 0, 2, 1, 0};
  int index = pruning::cornersOrientationToIndex(orientation);
  ASSERT_EQ(index, 412);
}

TEST(IndexationTest, testEdgesOrientationIdentityIsIndex0) {
  int orientation[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int index = pruning::edgesOrientationToIndex(orientation);
  ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testEdgesOrientationRPositionIsIndex562) {
  int orientation[12] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0};
  int index = pruning::edgesOrientationToIndex(orientation);
  ASSERT_EQ(index, 562);
}

TEST(IndexationTest, testLehmerCode3412Is16) {
  int permutation[4] = {3, 4, 1, 2};
  int index = pruning::lehmerCodeEncode(permutation, 4);
  ASSERT_EQ(index, 16);
}

TEST(IndexationTest, testLehmerCode12354Is1) {
  int permutation[5] = {1, 2, 3, 5, 4};
  int index = pruning::lehmerCodeEncode(permutation, 5);
  ASSERT_EQ(index, 1);
}

TEST(IndexationTest, testLehmerCode21543Is29) {
  int permutation[5] = {2, 1, 5, 4, 3};
  int index = pruning::lehmerCodeEncode(permutation, 5);
  ASSERT_EQ(index, 29);
}

TEST(IndexationTest, testLehmerCode5372154Is3223) {
  int permutation[7] = {5, 3, 7, 2, 1, 6, 4};
  int index = pruning::lehmerCodeEncode(permutation, 7);
  ASSERT_EQ(index, 3223);
}

TEST(IndexationTest, testLehmerCode7654321Is5039) {
  int permutation[7] = {7, 6, 5, 4, 3, 2, 1};
  int index = pruning::lehmerCodeEncode(permutation, 7);
  ASSERT_EQ(index, 5039);
}

TEST(IndexationTest, testLehmerCodeLargestPermutationIsULONGMAX) {
  int permutation[21] = {7,  12, 14, 4, 3, 20, 5,  9,  6,  11, 0,
                         18, 10, 16, 1, 2, 8,  17, 15, 19, 13};
  int index = pruning::lehmerCodeEncode(permutation, 21);
  ASSERT_EQ(index, ULONG_MAX);
}

TEST(IndexationTest, testCornersPermutationIdentityIsIndex0) {
  int permutation[8] = {1, 2, 3, 4, 5, 6, 7, 8};
  int index = pruning::cornersPermutationToIndex(permutation);
  ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testCornersPermutationRPositionIsIndex1230) {
  int permutation[8] = {1, 3, 7, 4, 5, 2, 6, 8};
  int index = pruning::cornersPermutationToIndex(permutation);
  ASSERT_EQ(index, 1230);
}

TEST(IndexationTest, testEdgesPermutationIdentityIsIndex0) {
  int permutation[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int index = pruning::edgesPermutationToIndex(permutation);
  ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testEdgesPermutationRPositionIsIndex18552630) {
  int permutation[12] = {1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12};
  int index = pruning::edgesPermutationToIndex(permutation);
  ASSERT_EQ(index, 18552630);
}

TEST(IndexationTest, testLREdgesPermutationToIndex) {
  int permutation[12] = {1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12};
  int index = pruning::lrEdgesPermutationToIndex(permutation);
  ASSERT_EQ(index, 168);
}

TEST(StateRecoveryTest, testCornerOrientationToIndex) {
  int orientation[8] = {0, 1, 2, 0, 0, 2, 1, 0};
  int index = pruning::cornersOrientationToIndex(orientation);
  int temp[8] = {0};
  pruning::indexToCornerOrientation(index, temp);
  ASSERT_THAT(temp, ElementsAre(0, 1, 2, 0, 0, 2, 1, 0));
}

TEST(StateRecoveryTest, testEdgesOrientationToIndex) {
  int orientation[12] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0};
  int index = pruning::edgesOrientationToIndex(orientation);
  int temp[12] = {0};
  pruning::indexToEdgeOrientation(index, temp);
  ASSERT_THAT(temp, ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(StateRecoveryTest, testLehmerCodeDecode) {
  int permutation[3] = {1, 3, 2};
  int index = pruning::lehmerCodeEncode(permutation, 3);
  int temp[3] = {0};
  pruning::lehmerCodeDecode(index, temp, 3);
  ASSERT_THAT(temp, ElementsAre(1, 3, 2));
}

TEST(StateRecoveryTest, testCornerPermutationToIndex) {
  int permutation[8] = {1, 3, 7, 4, 5, 2, 6, 8};
  int index = pruning::cornersPermutationToIndex(permutation);
  int temp[8] = {0};
  pruning::indexToCornerPermutation(index, temp);
  ASSERT_THAT(temp, ElementsAre(1, 3, 7, 4, 5, 2, 6, 8));
}

TEST(StateRecoveryTest, testEdgesPermutationToIndex) {
  int permutation[12] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int index = pruning::edgesPermutationToIndex(permutation);
  int temp[12] = {0};
  pruning::indexToEdgePermutation(index, temp);
  ASSERT_THAT(temp, ElementsAre(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1));
}

TEST(TableGenerationTest, testPhaseOneTableElementsAreGenerated) {
  std::vector<unsigned> table = pruning::PhaseOneTableGenerator().generate();
  ASSERT_EQ(std::find(table.begin(), table.end(), UINT32_MAX), table.end());
}

TEST(TableGenerationTest, testPhaseTwoTableElementsAreGenerated) {
  std::vector<std::vector<unsigned>> table =
      pruning::PhaseTwoTableGenerator().generate();
  for (auto row : table) {
    ASSERT_EQ(std::find(row.begin(), row.end(), UINT32_MAX), row.end());
  }
}
