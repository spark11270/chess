#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

public:
    // CONSTRUCTOR
    Rook(Board *b, Colour c, int row, int col);

    // OVERRIDE
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;
    ~Rook();
};

#endif
