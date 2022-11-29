#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include <string>;

enum PieceName {
    King = 0, 
    Queen, 
    Bishop, 
    Rook, 
    Knight, 
    Pawn
};

class Piece {
    PieceName type;
    Colour color;
    int row;
    int col;
    bool isFirstMove;

    public:
        Piece(PieceName type, Colour color, int row, int col);
        virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) = 0;
        PieceName getType();
        int getRow();
        int getColumn();
        Colour getColor();
        ~Piece();

};
#endif
