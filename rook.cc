#include "rook.h"

Rook::Rook(Colour c, int row, int col) : Piece(c, row, col) {}

bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= ) return false;
    if (finalCol >= 8) return false;
    if (initialRow == finalRow && initialCol == finalCol) return false;
    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    
    return false;
}

PieceName getType() {return PieceName::Rook;}
