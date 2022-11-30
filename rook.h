#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

public:
    Rook(Colour c, int row, int col);

    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
