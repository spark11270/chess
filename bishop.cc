#include "bishop.h"

Bishop::Bishop(Colour c, int row, int col) : Piece(c, row, col) {}

bool Bishop::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if ((finalCol - initialCol) == (finalRow - initialRow)) return true; // move diagnoally
    return false;
}

vector<pair<int, int>> Pawn::getPosMoves() {
    vector<pair<int, int>> moves;
    for (int i = 1; i <= row; ++i) {
        if (col - i >= 0) {
            // backward diagonal
            moves.push_back(make_pair(row - i, col - i));
            // forward diagonal
            moves.push_back(make_pair(row - i, col + i));
        }
    }
    for (int i = 1; i <= MAXCELL - row; ++i) {
        if (col + i <= MAXCELL) {
            // forward diagonal
            moves.push_back(make_pair(row + i, col - i));
            // bckward diagonal
            moves.push_back(make_pair(row + i, col + i));
        }
    }
    return moves;
}

PieceName Bishop::getType() {return PieceName::bishop;}
