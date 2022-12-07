#ifndef _LVL3_H_
#define _LVL3_H_

#include "lvl.h"
#include "move.h"

class Board;

class LVL3 : public LVL {
  public:
    LVL3();
    std::pair<std::pair<int, int>, std::pair<int, int>> getAIMove(std::shared_ptr<Board> board) override;
    ~LVL3();
};

#endif
