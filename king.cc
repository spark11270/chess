#include "king.h"


bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (((initialRow + 1) == finalRow || (initialRow - 1) == finalRow) && 
        ((initialCol + 1) == finalCol || (initialCol - 1) == finalCol)) return true; // check diagnoals

    if ((initialRow == finalRow) && ((initialCol + 1) == finalCol || (initialCol - 1) == finalCol)) return true; // moves left and right one square
    if ((initialCol == finalCol) && ((initialRow + 1 == finalRow) || initialRow - 1 == finalRow)) return true; // moves up and down one square

    return false;
}

PieceName getType() {return PieceName::King;}
