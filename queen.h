#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

public:
    Queen(Colour c, int row, int col);

    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;

};

#endif
