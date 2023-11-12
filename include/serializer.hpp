#ifndef SERIALIZER
#define SERIALIZER

#include <fstream>
#include <vector>

namespace serialization {
void serialize(const std::vector<unsigned> &v, std::ostream &os);
void deserialize(std::vector<unsigned> &v, std::istream &is);
void serialize(const std::vector<std::vector<unsigned>> &v, std::ostream &os);
void deserialize(std::vector<std::vector<unsigned>> &v, std::istream &is);
}  // namespace serialization
#endif