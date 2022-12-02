#include "bishop.h"

using namespace std;

Bishop::Bishop(Colour c, int row, int col) : Piece(c, row, col, PieceName::Bishop) {}

bool Bishop::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    if ((final.second - initial.second) == (final.first - initial.first)) return true; // move diagnoally
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

PieceName Bishop::getType() {return PieceName::Bishop;}
