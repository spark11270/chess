#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "colour.h"
#include <string>

class King;

class Player {
    std::string name;
    Colour colour;
    int score;

public:
    Player(std::string name, Colour colour, int score);

    std::string getName();
    Colour getColour();
    int getScore();

    virtual ~Player() = 0;
};

#endif
