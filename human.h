#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human : public Player {

public:
    Human(Colour colour);
    ~Human();

    void move(Board *board, std::pair<int, int> from, std::pair<int, int> to) override;
};

#endif
