#ifndef PIECE_H
#define PIECE_H

#include "colour.h"
#include "piecename.h"
#include <string>
#include <utility>
#include <vector>

const int MAXCELL = 8;

class Board;

class Piece {

    Board *b;  
    Colour colour;
    PieceName type;
    int mcount = 0;
    std::pair<int, int> coords;

    public:
        // CONSTRUCTOR
        Piece(Board *b, Colour c, PieceName type, int row, int col);

        // HELPERS
        bool outOfBounds(std::pair<int,int> initial, std::pair<int,int> final);

        // ACESSORS
        Board *getTheBoard();
        Colour getColour();
        int getNumMoves();
        std::pair<int, int> getCoords();

        // MODIFIERS
        void modifyCoords(std::pair<int,int> newCoords);
        void addMoves();
        void decrementMoves();

        // VIRTUAL
        virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) = 0;
        virtual std::vector<std::pair<int, int>> getPosMoves() = 0;
        virtual PieceName getType() = 0;

        // DESTRUCTOR
        virtual ~Piece() = 0;

};
#endif
