#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {

public:
    Pawn(Colour c, int row, int col);
    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) override;
    virtual bool isCheck() override;
    virtual bool isCheckmate() override;
    PieceName getType() override;

};

#endif
