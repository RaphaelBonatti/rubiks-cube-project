#ifndef PRUNING_TABLES
#define PRUNING_TABLES

#include <queue>
#include <string>
#include <vector>

#include "cube.hpp"
#include "indexer.hpp"

namespace pruning {

template <typename T>
class PhaseRunner {
   public:
    PhaseRunner(T &phase_table);
    std::vector<unsigned> run(Cube &cube);

   private:
    T phase_table;
    std::vector<unsigned> solution;

    unsigned findBestNextMove(const Cube &cube);
    unsigned getDistance(const Cube &cube);
};

template <typename T>
class PhaseTable {
   public:
    T table;
    std::vector<unsigned> moves;
    virtual unsigned &getTableValue(const Cube &cube) = 0;

   protected:
    std::string name;
    std::queue<Indexer> indices;
    void generateTable();
    virtual std::vector<Indexer> generateInitialStates();
    void update(const Cube &cube, unsigned distance);
    Indexer computeNextIndex(Indexer &index, unsigned move);
    void serialize();
    void deserialize();
    void initTable();
};

class PhaseOneTable : public PhaseTable<std::vector<unsigned>> {
   public:
    PhaseOneTable();
    unsigned &getTableValue(const Cube &cube);
};

class PhaseTwoTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
   public:
    PhaseTwoTable();
    unsigned &getTableValue(const Cube &cube);
};

class PhaseThreeTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
   public:
    PhaseThreeTable();
    unsigned &getTableValue(const Cube &cube);
    std::vector<Indexer> generateInitialStates();
};

class PhaseFourTable : public PhaseTable<std::vector<std::vector<unsigned>>> {
   public:
    PhaseFourTable();
    unsigned &getTableValue(const Cube &cube);
};

}  // namespace pruning

#endif