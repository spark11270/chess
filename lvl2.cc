#include "lvl2.h"
#include "move.h"
#include "board.h"
#include <vector>

using namespace std;

LVL2::LVL2() {}

pair<pair<int, int>, pair<int, int>> LVL2::getAIMove(Board *board) {
  vector<pair<shared_ptr<Piece>, pair<int, int>>> possibleMovePairs = board->getAllValidMoves(!board->isBlackTurn());
  
  pair<shared_ptr<Piece>, pair<int, int>> result;

  if (preferCaptureCheck(board, result, possibleMovePairs)) {
    return converter(result);
  }

  return converter(generateRandomMove(possibleMovePairs));
}