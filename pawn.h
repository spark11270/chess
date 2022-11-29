#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece {
    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
