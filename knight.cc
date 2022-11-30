#include "knight.h"

Knight::Knight(Colour c, int row, int col) : Piece(c, row, col) {}

bool isValidMove(int initialRow, int initialCol, int finalRow, int finalCol) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position
    if (((initialRow + 2) == finalRow) && (((initialCol + 1) == finalCol) || ((initialCol - 1) == finalCol))) return true; 
    if (((initialRow - 2) == finalRow) && (((initialCol + 1) == finalCol) || ((initialCol - 1) == finalCol))) return true;
    if (((initialCol - 2) == finalCol) && (((initialRow + 1) == finalRow) || ((initialRow - 1) == finalRow))) return true;
    if (((initialCol + 2) == finalCol) && (((initialRow + 1) == finalRow) || ((initialRow - 1) == finalRow))) return true;
    if (initialCol == finalCol) return true; //move vertically
    return false;
}

PieceName getType() {return PieceName::Knight;}
