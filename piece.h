#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecename.h"
#include <string>
#include <utility>
#include <vector>


const int MAXCELL = 8; // rows and columns are 0-7

class Board;

// Decorator for Cell
class Piece {
    Colour colour;
    std::pair<int, int> coords;
    PieceName type;
    Board *b;  
    bool isFirstMove = true;

    public:
        Piece(Colour color, int row, int col, PieceName type, Board *b);

        virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) = 0;
        virtual std::vector<std::pair<int, int>> getPosMoves() = 0;
        virtual PieceName getType() = 0;
        std::pair<int, int> getCoords();
        void setCoords(int r, int c);
        void modifyCoords(std::pair<int,int> &newCoords);
        Colour getColour();
        Board *getTheBoard();
        bool getIsFirstMove();
        void setIsFirstMove();

        virtual ~Piece() = 0;

};
#endif
