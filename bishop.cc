#include "bishop.h"

using namespace std;

Bishop::Bishop(Colour c, int row, int col) : Piece(c, row, col) {}

bool Bishop::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if ((finalCol - initialCol) == (finalRow - initialRow)) return true; // move diagnoally
    return false;
}

vector<pair<int, int>> Bishop::getPosMoves() {
    vector<pair<int, int>> moves;
    for (int i = 1; i <= getCoords().first; ++i) {
        if (getCoords().second - i >= 0) {
            // backward diagonal
            moves.push_back(make_pair(getCoords().first - i, getCoords().second - i));
            // forward diagonal
            moves.push_back(make_pair(getCoords().first - i, getCoords().second + i));
        }
    }
    for (int i = 1; i <= MAXCELL - getCoords().first; ++i) {
        if (getCoords().second + i <= MAXCELL) {
            // forward diagonal
            moves.push_back(make_pair(getCoords().first + i, getCoords().second - i));
            // bckward diagonal
            moves.push_back(make_pair(getCoords().first + i, getCoords().second + i));
        }
    }
    return moves;
}

PieceName Bishop::getType() {return PieceName::bishop;}
