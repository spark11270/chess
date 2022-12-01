#include "rook.h"

Rook::Rook(Colour c, int row, int col) : Piece{c, row, col} {}

bool Rook::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= 0) return false;
    if (finalCol >= 8) return false;
    if (initialRow == finalRow && initialCol == finalCol) return false;
    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    
    return false;
}

PieceName Rook::getType() {return PieceName::rook;}
