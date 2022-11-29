#ifndef ROOK_H
#define ROOK_H

class Rook : public Piece {
    Rook(Color color, int row, int col, bool isFirstMove);
    bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) override;

};

#endif
