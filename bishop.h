#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
