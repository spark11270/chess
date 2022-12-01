#ifndef _CELL_H_
#define _CELL_H_


class Piece;
class Board;

class Cell {
    int row;
    int col;
    Board *board;
    Piece *piece;

public:

    Cell(int row, int col, Board *board, Piece *piece);
    Cell(int row, int col, Board *board);
    

    Piece* getPiece();
    void addPiece(Piece *p);
    void removePiece();
    int getRow();
    int getCol();

    ~Cell();
};

#endif
