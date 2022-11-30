#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

public:
    Queen(Colour c, int row, int col);

    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;
    PieceName getType() override;

};

#endif
