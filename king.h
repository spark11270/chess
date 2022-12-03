#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Colour c, int row, int col, Board *theBoard);

    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;

};

#endif
