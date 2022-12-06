#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <utility>
#include <memory>
#include <vector>

class Move;
class Board;
class Piece;

class LVL {
  public:
    LVL();
    virtual ~LVL();

    std::pair<std::pair<int, int>, std::pair<int, int>> converter( \
      std::pair<std::shared_ptr<Piece>, std::pair<int, int>> movePair
    );

    std::pair<std::shared_ptr<Piece>, std::pair<int, int>> generateRandomMove( \
      std::vector<std::pair<std::shared_ptr<Piece>, std::pair<int, int>>> possibleMovePairs);

    bool preferCaptureCheck( \
      std::shared_ptr<Board> board, \
      std::pair<std::shared_ptr<Piece>, std::pair<int, int>> &result, \
      std::vector<std::pair<std::shared_ptr<Piece>, std::pair<int, int>>> possibleMovePairs);

    virtual std::pair<std::pair<int, int>, std::pair<int, int>> getAIMove(std::shared_ptr<Board> board) = 0;
};

#endif
