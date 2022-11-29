#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>

class Cell;
class Piece;

class Move {
    std::vector<Cell> sequence;
    std::vector<Piece> caught;

    Move(std::vector<Cell> sequence, std::vector<Piece> caught);
};

#endif
