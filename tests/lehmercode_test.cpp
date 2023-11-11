#include "lehmercode.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using testing::ElementsAre;

TEST(IndexationTest, testLehmerCode3412Is16) {
    unsigned permutation[4] = {3, 4, 1, 2};
    unsigned index = lehmerCodeEncode(permutation, 4);
    ASSERT_EQ(index, 16);
}

TEST(IndexationTest, testLehmerCode12354Is1) {
    unsigned permutation[5] = {1, 2, 3, 5, 4};
    unsigned index = lehmerCodeEncode(permutation, 5);
    ASSERT_EQ(index, 1);
}

TEST(IndexationTest, testLehmerCode21543Is29) {
    unsigned permutation[5] = {2, 1, 5, 4, 3};
    unsigned index = lehmerCodeEncode(permutation, 5);
    ASSERT_EQ(index, 29);
}

TEST(IndexationTest, testLehmerCode5372154Is3223) {
    unsigned permutation[7] = {5, 3, 7, 2, 1, 6, 4};
    unsigned index = lehmerCodeEncode(permutation, 7);
    ASSERT_EQ(index, 3223);
}

TEST(IndexationTest, testLehmerCode7654321Is5039) {
    unsigned permutation[7] = {7, 6, 5, 4, 3, 2, 1};
    unsigned index = lehmerCodeEncode(permutation, 7);
    ASSERT_EQ(index, 5039);
}

TEST(IndexationTest, testLehmerCodeLargestPermutationIsUINT32_MAX) {
    unsigned permutation[21] = {7,  12, 14, 4, 3, 20, 5,  9,  6,  11, 0,
                                18, 10, 16, 1, 2, 8,  17, 15, 19, 13};
    unsigned index = lehmerCodeEncode(permutation, 21);
    ASSERT_EQ(index, UINT32_MAX);
}

TEST(StateRecoveryTest, testLehmerCodeDecode) {
    unsigned permutation[3] = {1, 3, 2};
    unsigned index = lehmerCodeEncode(permutation, 3);
    unsigned temp[3] = {0};
    lehmerCodeDecode(index, temp, 3);
    ASSERT_THAT(temp, ElementsAre(1, 3, 2));
}