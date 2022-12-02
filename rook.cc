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
    for (int i = 1; i <= getCoords().first; ++i) {
        moves.push_back(make_pair(getCoords().first - i, getCoords().second));
    }
    for (int i = 1; i <= MAXCELL - getCoords().first; ++i) {
        moves.push_back(make_pair(getCoords().first + i, getCoords().second));
    }
    // horizontal
    for (int i = 1; i <= getCoords().second; ++i) {
        moves.push_back(make_pair(getCoords().first, getCoords().second - i));
    }
    for (int i = 1; i <= MAXCELL - getCoords().second; ++i) {
        moves.push_back(make_pair(getCoords().first, getCoords().second + i));
    }
    return moves;
}

PieceName Rook::getType() {return PieceName::rook;}
