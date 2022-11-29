#include "rook.h"


Rook::Rook(Color color, int row, int col, bool isFirstMove) : color{color}, row{row}, col{col}, isFirstMove{false} {}

isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    // if (initialRow == finalRow && initialCol == finalCol)
    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    return false;
}
