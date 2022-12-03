#include "lvl1.h"
#include "board.h"
#include <vector>
#include <memory>
#include <utility>

using namespace std;

LVL1::LVL1() {}

pair<pair<int, int>, pair<int, int>> LVL1::getAIMove(Board *board) {
  vector<pair<shared_ptr<Piece>, pair<int, int>>> possibleMovePairs = board->getAllValidMoves(board->isWhiteTurn());
  return converter(generateRandomMove(possibleMovePairs));
}
