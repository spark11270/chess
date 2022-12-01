#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>

class Cell;
class Piece;

class Move {
    Piece* captured;
    Piece* moving;
    int c_t; // t = to and f = from
    int r_t;
    int c_f;
    int r_f;

    Move(int c_f, int r_f, int c_t, int r_t, Piece* captured, Piece* moving);
};

#endif
