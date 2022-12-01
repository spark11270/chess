#include "king.h"

King::King(Colour c, int row, int col) : Piece(c, row, col) {}

bool King::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (((initialRow + 1) == finalRow || (initialRow - 1) == finalRow) && 
        ((initialCol + 1) == finalCol || (initialCol - 1) == finalCol)) return true; // check diagnoals

    if ((initialRow == finalRow) && ((initialCol + 1) == finalCol || (initialCol - 1) == finalCol)) return true; // moves left and right one square
    if ((initialCol == finalCol) && ((initialRow + 1 == finalRow) || initialRow - 1 == finalRow)) return true; // moves up and down one square

    return false;
}

vector<pair<int, int>> King::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
    moves.push_back(make_pair(row + 1, col));
    moves.push_back(make_pair(row - 1, col));
    // horizontal
    moves.push_back(make_pair(row, col + 1));
    moves.push_back(make_pair(row, col - 1));
    // forward diagonal
    moves.push_back(make_pair(row + 1, col - 1));
    moves.push_back(make_pair(row - 1, col + 1));
    // backward diagonal
    moves.push_back(make_pair(row + 1, col + 1));
    moves.push_back(make_pair(row - 1, col - 1));
    return moves;
}

PieceName King::getType() {return PieceName::king;}
