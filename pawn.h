#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#include <iostream>
#include <utility>

class Pawn : public Piece {
public:
    Pawn(Colour c, int row, int col, Board *theBoard);
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;
};

#endif
