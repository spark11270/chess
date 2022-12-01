#include "rook.h"

using namespace std;

Rook::Rook(Colour c, int row, int col) : Piece{c, row, col} {}

bool Rook::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove)  {
    if (finalRow >= MAXCELL) return false;
    if (finalCol >= MAXCELL) return false;
    if (initialRow == finalRow && initialCol == finalCol) return false;
    if (initialRow == finalRow) return true; //move horizontally
    if (initialCol == finalCol) return true; //move vertically
    
    return false;
}

vector<pair<int, int>> Rook::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
    for (int i = 1; i <= row; ++i) {
        moves.push_back(make_pair(row - i, col));
    }
    for (int i = 1; i <= MAXCELL - row; ++i) {
        moves.push_back(make_pair(row + i, col));
    }
    // horizontal
    for (int i = 1; i <= col; ++i) {
        moves.push_back(make_pair(row, col - i));
    }
    for (int i = 1; i <= MAXCELL - col; ++i) {
        moves.push_back(make_pair(row, col + i));
    }
    return moves;
}

PieceName Rook::getType() {return PieceName::rook;}
