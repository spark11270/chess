#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {

public:
    Rook(Colour c, int row, int col);

    virtual bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove)  override;
    //virtual bool isCheck() override;
    //virtual bool isCheckmate() override;
    PieceName getType() override;

};

#endif
