#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {

public:
    Bishop(Colour c, int row, int col);

    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) override;
    virtual bool isCheck() override;
    virtual bool isCheckmate() override;
    PieceName getType() override;

};

#endif
