#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include <string>
#include <utility>
#include <vector>

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
    std::pair<int, int> coords;

    public:
        Piece(Colour color, int row, int col);

        virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) = 0;
        virtual std::vector<std::pair<int, int>> getPosMoves() = 0;
        virtual bool isCheck() = 0;
        virtual bool isCheckmate() = 0;
        virtual PieceName getType() = 0;
        std::pair<int, int> getCoords();
        void setCoords(int r, int c);
        Colour getColour();

        ~Piece();

};
#endif
