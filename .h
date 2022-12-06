#ifndef _LVL1_H_
#define _LVL1_H_

#include <utility>

#include "lvl.h"
#include "move.h"

class Board;

class LVL1 : public LVL {
  public:
    LVL1();
    std::pair<std::pair<int, int>, std::pair<int, int>> getAIMove(std::shared_ptr<Board> board) override;
};

#endif
