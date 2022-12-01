#include "bishop.h"

Bishop::Bishop(Colour c, int row, int col) : Piece(c, row, col) {}

bool Bishop::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if ((finalCol - initialCol) == (finalRow - initialRow)) return true; // move diagnoally
    return false;
}

PieceName Bishop::getType() {return PieceName::bishop;}
