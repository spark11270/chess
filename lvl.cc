#include <memory>
#include <vector>

#include "lvl.h"

using namespace std;

LVL::LVL() {}

LVL::~LVL() {}

pair<pair<int, int>, pair<int, int>> LVL::generateRandomMove( \
  const vector<pair<pair<int, int>, pair<int, int>>> possibleMovePairs \
) {
  time_t t;
  int size = possibleMovePairs.size();
  srand(time(&t));
  int randomInd = rand() % size;
  return possibleMovePairs.at(randomInd);
}