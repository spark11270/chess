#include "pawn.h"


bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds

    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (isFirstMove == true) { // can move 2 square forwards only if first move
        if ((initialRow + 2) == finalRow) return true;
    }

    if ((initialRow + 1) == finalRow) return true;
    
    return false;
}

PieceName getType() {return PieceName::Pawn;}
