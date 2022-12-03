#include "lvl1.h"
#include "move.h"
#include "board.h"
#include <vector>

using namespace std;

LVL1::LVL1() {}

pair<pair<int, int>, pair<int, int>> LVL1::getAIMove(Board *board) {
  vector<pair<pair<int, int>, pair<int, int>>> possibleMovePairs = board->getAllValidMoves(board->isWhiteTurn());
  return generateRandomMove(possibleMovePairs);
}