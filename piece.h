#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "cell.h"
#include <string>

enum PieceName {
    king = 0, 
    queen, 
    bishop, 
    rook, 
    knight, 
    pawn
};

const int MAXCELL = 8; // rows and columns are 0-7

// Decorator for Cell
class Piece {
    PieceName type;   
    Colour colour;
    int row;
    int col;

    public:
        Piece(Colour colour, int row, int col);
        virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) = 0;
        virtual PieceName getType() = 0;
        int getRow();
        int getColumn();
        Colour getColour();
};
#endif
