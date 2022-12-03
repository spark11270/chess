#include "rook.h"
#include "board.h"

using namespace std;

Rook::Rook(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Rook, theBoard} {}

bool Rook::isValidMove(std::pair<int, int> initial, std::pair<int, int> final)  {

    if (final.first >= MAXCELL) return false;
    if (final.second >= MAXCELL) return false;
    if (initial.first == final.first && initial.second == final.second) return false;

    // move horizontally
    if (initial.first == final.first) {
        int r1 = initial.first;
        if (final.second > initial.second) {
            for (int i = initial.second + 1; i < final.second; ++i) {
            // obstacle blocking path
            if (getTheBoard()->hasObstacle(make_pair(r1, i))) return false;
            }
        } else {
            for (int i = final.second - 1; i < initial.second; --i) {
            // obstacle blocking path
            if (getTheBoard()->hasObstacle(make_pair(r1, i))) return false;
            }
        }
        return true;
    // move vertically
    } else if (initial.second == final.second) {
        int c1 = initial.second;
        if (final.first > initial.first) {
            for (int i = initial.first + 1; i < final.first; ++i) {
            // obstacle blocking path
            if (getTheBoard()->hasObstacle(make_pair(i, c1))) return false;
            }
        } else {
            for (int i = final.first - 1; i < initial.first; --i) {
            // obstacle blocking path
            if (getTheBoard()->hasObstacle(make_pair(i, c1))) return false;
            }
        }
        return true;
    }
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
