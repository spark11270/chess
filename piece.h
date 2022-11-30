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

const int MAXCELL = 8; // rows and columns are 0-7

class Piece {
    PieceName type;   
    Colour colour;
    int row;
    int col;
    bool isFirstMove;

    public:
        Piece(Colour color, int row, int col);

        virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) = 0;
        virtual bool isCheck() = 0;
        virtual bool isCheckmate() = 0;
        virtual PieceName getType() = 0;
        int getRow();
        int getColumn();
        Colour getColour();

        ~Piece();

};
#endif
