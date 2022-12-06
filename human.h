#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human : public Player {

public:
    Human(Colour colour);
    ~Human();

    char getType() override;
    void move(std::shared_ptr<Board> board, std::pair<int, int> from, std::pair<int, int> to) override;
};

#endif
