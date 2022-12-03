#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <utility>

class Move;
class Board;
class Piece;

class LVL {
  public:
    LVL();
    virtual ~LVL();

    std::pair<std::pair<int, int>, std::pair<int, int>> generateRandomMove( \
      const std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> possibleMovePairs \
    );
    virtual std::pair<std::pair<int, int>, std::pair<int, int>> getAIMove(Board *board) = 0;
};

#endif