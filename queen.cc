#include "queen.h"

Queen::Queen(Colour c, int row, int col) : Piece(c, row, col) {}

bool Queen::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (initialRow == finalRow) return true; // move along same row
    if (initialCol == finalCol) return true; // move along the same col
    if ((finalCol - initialCol) == (finalRow - initialRow)) return true; // move diagnoally
    return false;
}

PieceName Queen::getType() {return PieceName::queen;}
