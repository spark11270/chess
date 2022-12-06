#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "colour.h"
#include <string>
#include <memory>

class King;
class Board;

class Player {
    Colour colour;
    int score;

public:
    Player(Colour colour, int score);
    virtual ~Player() = 0;

    Colour getColour();
    int getScore();
    virtual char getType() = 0;

    void updateScore(); // increment score
    void resetScore();
    virtual void move(std::shared_ptr<Board> board, std::pair<int, int> from, std::pair<int, int> to) = 0;
};

#endif
