#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "player.h"

class Human : public Player {

public:
    Human(Colour colour);
    virtual char getType() override;
    
    ~Human();
};

#endif
