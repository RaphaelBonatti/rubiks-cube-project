#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>

#include "pruningtables.hpp"

using std::cout;
using testing::ElementsAre;
using testing::Test;

TEST(IndexationTest, testCornersOrientationIdentityIsIndex0) {
    unsigned orientation[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    unsigned index = pruning::cornersOrientationToIndex(orientation);
    ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testCornersOrientationRPositionIsIndex412) {
    unsigned orientation[8] = {0, 1, 2, 0, 0, 2, 1, 0};
    unsigned index = pruning::cornersOrientationToIndex(orientation);
    ASSERT_EQ(index, 412);
}

TEST(IndexationTest, testEdgesOrientationIdentityIsIndex0) {
    unsigned orientation[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned index = pruning::edgesOrientationToIndex(orientation);
    ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testEdgesOrientationRPositionIsIndex562) {
    unsigned orientation[12] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0};
    unsigned index = pruning::edgesOrientationToIndex(orientation);
    ASSERT_EQ(index, 562);
}

TEST(IndexationTest, testCornersPermutationIdentityIsIndex0) {
    unsigned permutation[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    unsigned index = pruning::cornersPermutationToIndex(permutation);
    ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testCornersPermutationRPositionIsIndex1230) {
    unsigned permutation[8] = {1, 3, 7, 4, 5, 2, 6, 8};
    unsigned index = pruning::cornersPermutationToIndex(permutation);
    ASSERT_EQ(index, 1230);
}

TEST(IndexationTest, testEdgesPermutationIdentityIsIndex0) {
    unsigned permutation[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    unsigned index = pruning::edgesPermutationToIndex(permutation);
    ASSERT_EQ(index, 0);
}

TEST(IndexationTest, testEdgesPermutationRPositionIsIndex18552630) {
    unsigned permutation[12] = {1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12};
    unsigned index = pruning::edgesPermutationToIndex(permutation);
    ASSERT_EQ(index, 18552630);
}

TEST(IndexationTest, testLREdgesPermutationToIndex) {
    unsigned permutation[12] = {1, 7, 3, 4, 5, 2, 10, 8, 9, 6, 11, 12};
    unsigned index = pruning::udEdgesPermutationToIndex(permutation);
    ASSERT_EQ(index, 168);
}

TEST(StateRecoveryTest, testCornerOrientationToIndex) {
    unsigned orientation[8] = {0, 1, 2, 0, 0, 2, 1, 0};
    unsigned index = pruning::cornersOrientationToIndex(orientation);
    unsigned temp[8] = {0};
    pruning::indexToCornerOrientation(index, temp);
    ASSERT_THAT(temp, ElementsAre(0, 1, 2, 0, 0, 2, 1, 0));
}

TEST(StateRecoveryTest, testEdgesOrientationToIndex) {
    unsigned orientation[12] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0};
    unsigned index = pruning::edgesOrientationToIndex(orientation);
    unsigned temp[12] = {0};
    pruning::indexToEdgeOrientation(index, temp);
    ASSERT_THAT(temp, ElementsAre(0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0));
}

TEST(StateRecoveryTest, testCornerPermutationToIndex) {
    unsigned permutation[8] = {1, 3, 7, 4, 5, 2, 6, 8};
    unsigned index = pruning::cornersPermutationToIndex(permutation);
    unsigned temp[8] = {0};
    pruning::indexToCornerPermutation(index, temp);
    ASSERT_THAT(temp, ElementsAre(1, 3, 7, 4, 5, 2, 6, 8));
}

TEST(StateRecoveryTest, testEdgesPermutationToIndex) {
    unsigned permutation[12] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    unsigned index = pruning::edgesPermutationToIndex(permutation);
    unsigned temp[12] = {0};
    pruning::indexToEdgePermutation(index, temp);
    ASSERT_THAT(temp, ElementsAre(12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1));
}

TEST(TableGenerationTest, testPhaseOneTableElementsAreGenerated) {
    std::vector<unsigned> table = pruning::PhaseOneTable().table;
    ASSERT_EQ(std::find(table.begin(), table.end(), UINT32_MAX), table.end());
}

TEST(TableGenerationTest, testPhaseTwoTableElementsAreGenerated) {
    std::vector<std::vector<unsigned>> table = pruning::PhaseTwoTable().table;
    for (auto row : table) {
        ASSERT_EQ(std::find(row.begin(), row.end(), UINT32_MAX), row.end());
    }
}

TEST(TableGenerationTest, testPhaseThreeTableElementsAreGenerated) {
    std::vector<std::vector<unsigned>> table = pruning::PhaseThreeTable().table;
    for (auto row : table) {
        ASSERT_EQ(std::find(row.begin(), row.end(), UINT32_MAX), row.end());
    }
}

TEST(TableGenerationTest, testPhaseFourTableElementsAreGenerated) {
    std::vector<std::vector<unsigned>> table = pruning::PhaseFourTable().table;
    for (auto row : table) {
        ASSERT_EQ(std::find(row.begin(), row.end(), UINT32_MAX), row.end());
    }
}