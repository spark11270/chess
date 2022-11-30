#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"
#include <string>
#include <vector>

enum class Level {L1, L2, L3, L4};

class Move;

class Computer : public Player {
    Level lvl;

public:
    Computer(std::string name, Colour c, int score, Level lvl);

    virtual vector<Move> getAIMoves();

    virtual ~Computer() = 0;
};

#endif
