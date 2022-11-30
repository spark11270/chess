#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human : public Player {

public:
    Human(std::string name, Colour colour, int score);
    
    ~Human();
};

#endif
