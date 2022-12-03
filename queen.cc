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

    for (int i = 0; i < MAXCELL; ++i) {
        pair<int, int> pos;
        pos.first = i;
        pos.second = getCoords().second;
        if (i != getCoords().first) {
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
    }
    // horizontal
     for (int j = 0; j < MAXCELL; ++j) {
         pair<int, int> pos;
         pos.first = getCoords().first;
         pos.second = j;
        if (j != getCoords().second) {
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
    }

    // diagonal
    for (int k = 1; k < MAXCELL; ++k) {
        pair<int, int> pos;
        // before piece
        if (k <= getCoords().first) {
            if (getCoords().second - k >= 0) {
                pos.first = getCoords().first - k;
                pos.second = getCoords().second - k;
                if (isValidMove(getCoords(), pos)) {
                        moves.push_back(pos);
                }
            }
            if (getCoords().second + k < MAXCELL) {
                pos.first = getCoords().first - k;
                pos.second = getCoords().second + k;
                if (isValidMove(getCoords(), pos)) {
                        moves.push_back(pos);
                }
            }
        }
        // after piece
        if (k > getCoords().first) {
            int l = k - getCoords().first;
            if (getCoords().second - l >= 0 ) {
                pos.first = k;
                pos.second = getCoords().second - l;
                if (isValidMove(getCoords(), pos)) {
                        moves.push_back(pos);
                }
            } 
            if ( getCoords().second + l < MAXCELL) {
                pos.first = k;
                pos.second = getCoords().second + l;
                if (isValidMove(getCoords(), pos)) {
                        moves.push_back(pos);
                }
            }
        }
    }

    return moves;
}

PieceName Queen::getType() {return PieceName::Queen;}
