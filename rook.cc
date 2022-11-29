#include "rook.h"


bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds

    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    
    return false;
}

PieceName getType() {return PieceName::Rook;}
