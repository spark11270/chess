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

vector<pair<int, int>> Queen::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
    for (int i = 1; i <= row; ++i) {
        moves.push_back(make_pair(row - i, col));
        // backward diagonal
        if (col - i >= 0) {
            moves.push_back(make_pair(row - i, col - i));
        }
    }
    for (int i = 1; i <= MAXCELL - row; ++i) {
        moves.push_back(make_pair(row + i, col));
        // backward diagonal
        if (col + i <= MAXCELL) {
            moves.push_back(make_pair(row + i, col + i));
        }
    }
    // horizontal
    for (int i = 1; i <= col; ++i) {
        moves.push_back(make_pair(row, col - i));
        // forward diagonal
        if (row - i >= 0) {
            moves.push_back(make_pair(row - i, col - i));
        }
    }
    for (int i = 1; i <= MAXCELL - col; ++i) {
        moves.push_back(make_pair(row, col + i));
        // forward diagonal
        if (row + i <= MAXCELL) {
            moves.push_back(make_pair(row + i, col + i));
        }
    }
    return moves;
}

PieceName Queen::getType() {return PieceName::queen;}
