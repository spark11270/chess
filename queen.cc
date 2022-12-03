#include "queen.h"
#include "board.h"

using namespace std;

Queen::Queen(Colour c, int row, int col, Board *theBoard) : Piece(c, row, col, PieceName::Queen, theBoard) {}

bool Queen::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds

    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    // my own item in the final
    if (getTheBoard()->hasAlly(getColour(), final)) return false;

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
    } else if (abs(final.second - initial.second) == abs(final.first - initial.first)) {
        int x = 1;
        int y = 1;

        pair<int, int> xyCoords;
        xyCoords.first = initial.first;
        xyCoords.second = initial.second;
        
        if ((final.second - initial.second) < 0) {
            x = -1;
        }
        if ((final.first - initial.first) < 0) {
            y = -1;
        }

        pair<int, int> dir;
        dir.first = y;
        dir.second = x;
        xyCoords.first += dir.first;
        xyCoords.second += dir.second;

        for (int i = 1; i < abs(final.second - initial.second); ++i) {
            if(getTheBoard()->hasObstacle(xyCoords)) return false;
            xyCoords.first += dir.first;
            xyCoords.second += dir.second;
        }
        return true;
    }

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
