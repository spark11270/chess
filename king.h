#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
