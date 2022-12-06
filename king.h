#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {

public:
    // CONSTRUCTOR
    King(std::shared_ptr<Board> b, Colour c, int row, int col);

    // OVERRIDE
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;
};

#endif
