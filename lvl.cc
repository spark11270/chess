#include <memory>
#include <vector>
#include <utility>

#include "lvl.h"
#include "board.h"
#include "piece.h"

using namespace std;

LVL::LVL() {}

LVL::~LVL() {}

pair<pair<int, int>, pair<int, int>> LVL::converter( \
  pair<shared_ptr<Piece>, pair<int, int>> movePair \
) {
  return make_pair(movePair.first->getCoords(), movePair.second);
}

pair<shared_ptr<Piece>, pair<int, int>> LVL::generateRandomMove( \
  vector<pair<shared_ptr<Piece>, pair<int, int>>> possibleMovePairs \
) {
  time_t t;
  int size = possibleMovePairs.size();
  srand(time(&t));
  int randomInd = rand() % size;
  return possibleMovePairs.at(randomInd);
}


bool LVL::preferCaptureCheck( \
  Board *board, \
  pair<shared_ptr<Piece>, pair<int, int>> &result, \
  vector<pair<shared_ptr<Piece>, pair<int, int>>> possibleMovePairs
) {
  for (auto &movePair : possibleMovePairs) {
    if (board->willLeadToCheck(movePair.second)) {
      result = movePair;
      return true;
    }
  }
  return false;
}