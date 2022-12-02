#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"
#include <string>
#include <vector>

class Move;

class Computer : public Player {
    int lvl;

public:
    Computer(Colour c, int lvl);

    virtual std::vector<Move> getAIMoves();
    char getType();

    ~Computer();
};

#endif
