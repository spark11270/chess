#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#include <iostream>
#include <utility>

class Pawn : public Piece {

public:
    // CONSTRUCTOR
    Pawn(Board *b, Colour c, int row, int col);

    // OVERRIDE
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;
};

#endif
