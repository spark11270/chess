#ifndef _LVL2_H_
#define _LVL2_H_

#include "lvl.h"
#include "move.h"

class Board;

class LVL2 : public LVL {
  public:
    LVL2();
    std::pair<std::pair<int, int>, std::pair<int, int>> getAIMove(std::shared_ptr<Board> board) override;
};

#endif
