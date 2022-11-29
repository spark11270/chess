#include "bishop.h"


bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if ((finalCol - initialCol) == (finalRow - initialRow)) return true; // move diagnoally
    return false;
}

PieceName getType() {return PieceName::Bishop;}
