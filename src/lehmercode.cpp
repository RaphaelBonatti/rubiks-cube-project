#include "lehmercode.hpp"

unsigned lehmerCodeEncode(const unsigned permutation[], unsigned size) {
    unsigned result = 0;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            result = result + unsigned(permutation[i] > permutation[j]);
        }
        result *= size - 1 - i;
    }
    return result;
}

void lehmerCodeDecode(unsigned index, unsigned permutation[], unsigned size) {
    permutation[size - 1] = 1;
    for (int i = size - 2; i >= 0; --i) {
        permutation[i] = 1 + (index % (size - i));
        index = (index - (index % (size - i))) / (size - i);
        for (int j = i + 1; j < size; ++j) {
            permutation[j] = permutation[j] + unsigned(permutation[j] >= permutation[i]);
        }
    }
}