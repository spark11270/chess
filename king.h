#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece {
public:
    King(Colour c, int row, int col);

    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;

};

#endif
