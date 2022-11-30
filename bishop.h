#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

public:
    Bishop(Colour c, int row, int col);

    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
