#include "rook.h"


Rook::Rook(Colour c, int row, int col) : colour{colour}, row{row}, col{col}, isFirstMove{false} {}

bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= 8) return false;
    if (finalCol >= 8) return false;
    // if (initialRow == finalRow && initialCol == finalCol)
    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    return false;
}

PieceName getType() {return PieceName::Rook;}