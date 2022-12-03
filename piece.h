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
    Board *theBoard;
    PieceName type;   
    Colour colour;
    std::pair<int, int> coords;
    bool isFirstMove;

    public:
        Piece(Colour color, int row, int col, PieceName type, Board *theBoard);

        virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) = 0;
        virtual std::vector<std::pair<int, int>> getPosMoves() = 0;
        virtual PieceName getType() = 0;
        std::pair<int, int> getCoords();
        void setCoords(int r, int c);
        void modifyCoords(std::pair<int,int> &newCoords);
        Colour getColour();
        bool isMine(Piece *p);

        virtual ~Piece() = 0;

};
#endif
