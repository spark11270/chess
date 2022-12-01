#include "pawn.h"

Pawn::Pawn(Colour c, int row, int col) : Piece{c, row, col} {}

bool Pawn::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds

    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (isFirstMove == true) { // can move 2 square forwards only if first move
        if ((initialRow + 2) == finalRow) return true;
    }

    if ((initialRow + 1) == finalRow) return true;
    
    return false;
}

/*
bool Pawn::isCheck() {
    
}

bool Pawn::isCheckmate() {
    
}
*/

PieceName Pawn::getType() {return PieceName::pawn;}
