#ifndef _CELL_H_
#define _CELL_H_

#include "subject.h"

class Piece;
class Board;

class Cell : public Subject{
    int row;
    int col;
    Board *board;
    Piece *piece;

public:

    Cell(int row, int col, Board *board, Piece *piece);
    
    void addPiece(Piece *p);
    void removePiece();
    int getRow();
    int getCol();

    ~Cell();
};

#endif
