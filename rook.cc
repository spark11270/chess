#include "rook.h"

using namespace std;

Rook::Rook(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Rook, theBoard} {}

bool Rook::isValidMove(std::pair<int, int> initial, std::pair<int, int> final)  {
    if (final.first >= MAXCELL) return false;
    if (final.second >= MAXCELL) return false;
    if (initial.first == final.first && initial.second == final.second) return false;
    if (initial.first == final.first) return true; //move horizontally
    if (initial.second == final.second) return true; //move vertically
    
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

PieceName Rook::getType() {return PieceName::Rook;}
