#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool isFirstMove;
public:
    Pawn(Colour c, int row, int col);
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    void setIsFirstMove();
    PieceName getType() override;
};

#endif
