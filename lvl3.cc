#include "lvl3.h"
#include "move.h"
#include "board.h"
#include <vector>

using namespace std;

LVL3::LVL3() {}

pair<pair<int, int>, pair<int, int>> LVL3::getAIMove(Board *board) {
  vector<pair<shared_ptr<Piece>, pair<int, int>>> myMovePairs = board->getAllValidMoves(!board->isBlackTurn());
  vector<pair<shared_ptr<Piece>, pair<int, int>>> opponentMovePairs = board->getAllValidMoves(board->isBlackTurn());
  
  for (auto myPair : myMovePairs) {
    bool willOpponentCaptureFrom = false;
    bool willOpponentCaptureTo = false;

    for (auto &opponentPair : opponentMovePairs) {
      if (myPair.first->getCoords() == opponentPair.second) {
        willOpponentCaptureFrom = true;
      }
    }

    for (auto &opponentPair : opponentMovePairs) {
      if (myPair.second == opponentPair.first->getCoords()) {
        willOpponentCaptureTo = true;
      }
    }

    if (willOpponentCaptureFrom && !willOpponentCaptureTo) {
      return converter(myPair);
    }
  }

  pair<shared_ptr<Piece>, pair<int, int>> result;
  if (preferCaptureCheck(board, result, myMovePairs)) {
    return converter(result);
  }

  return converter(generateRandomMove(myMovePairs));
}