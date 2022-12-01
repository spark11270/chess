#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool isFirstMove;
public:
    Pawn(Colour c, int row, int col);
    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) override;
    virtual std::vector<pair<int, int>> getPosMoves() = 0;
    PieceName getType() override;
};

#endif
