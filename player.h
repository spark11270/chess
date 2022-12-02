#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "colour.h"
#include <string>

class King;

class Player {
    Colour colour;
    int score;

public:
    Player(Colour colour, int score);

    Colour getColour();
    int getScore();
    void updateScore(); // increment score
    virtual char getType() = 0;

    virtual ~Player() = 0;
};

#endif
