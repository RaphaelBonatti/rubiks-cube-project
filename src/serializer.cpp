#include "serializer.hpp"

#include <vector>

using std::istream;
using std::ostream;
using std::vector;

void serialization::serialize(const vector<unsigned> &v, ostream &os) {
    size_t vsize = v.size();
    os.write((char *)&vsize, sizeof(vsize));
    os.write((char *)&v[0], vsize * sizeof(unsigned));
}

void serialization::deserialize(vector<unsigned> &v, istream &is) {
    size_t vsize;
    is.read((char *)&vsize, sizeof(vsize));
    v.resize(vsize);
    is.read((char *)&v[0], vsize * sizeof(unsigned));
}

void serialization::serialize(const vector<vector<unsigned>> &v, ostream &os) {
    size_t vsize = v.size();
    os.write((char *)&vsize, sizeof(vsize));
    for (size_t i = 0; i < vsize; ++i) {
        serialize(v[i], os);
    }
}

void serialization::deserialize(vector<vector<unsigned>> &v, istream &is) {
    size_t vsize;
    is.read((char *)&vsize, sizeof(vsize));
    v.resize(vsize);
    for (size_t i = 0; i < vsize; ++i) {
        deserialize(v[i], is);
    }
}
