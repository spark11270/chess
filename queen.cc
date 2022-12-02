#include "queen.h"

using namespace std;

Queen::Queen(Colour c, int row, int col) : Piece(c, row, col, PieceName::Queen) {}

bool Queen::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    if (initial.first == final.first) return true; // move along same row
    if (initial.second == final.second) return true; // move along the same col
    if ((final.second - initial.second) == (final.first - initial.first)) return true; // move diagnoally
    return false;
}

vector<pair<int, int>> Queen::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
    for (int i = 1; i <= getCoords().first; ++i) {
        moves.push_back(make_pair(getCoords().first - i, getCoords().second));
        // backward diagonal
        if (getCoords().second - i >= 0) {
            moves.push_back(make_pair(getCoords().first - i, getCoords().second - i));
        }
    }
    for (int i = 1; i <= MAXCELL - getCoords().first; ++i) {
        moves.push_back(make_pair(getCoords().first + i, getCoords().second));
        // backward diagonal
        if (getCoords().second + i <= MAXCELL) {
            moves.push_back(make_pair(getCoords().first + i, getCoords().second + i));
        }
    }
    // horizontal
    for (int i = 1; i <= getCoords().second; ++i) {
        moves.push_back(make_pair(getCoords().first, getCoords().second - i));
        // forward diagonal
        if (getCoords().first - i >= 0) {
            moves.push_back(make_pair(getCoords().first - i, getCoords().second - i));
        }
    }
    for (int i = 1; i <= MAXCELL - getCoords().second; ++i) {
        moves.push_back(make_pair(getCoords().first, getCoords().second + i));
        // forward diagonal
        if (getCoords().first + i <= MAXCELL) {
            moves.push_back(make_pair(getCoords().first + i, getCoords().second + i));
        }
    }
    return moves;
}

PieceName Queen::getType() {return PieceName::Queen;}
