#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
