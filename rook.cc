#include <utility>

#include "rook.h"
#include "board.h"

using namespace std;

Rook::Rook(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Rook, theBoard} {}

bool Rook::isValidMove(std::pair<int, int> initial, std::pair<int, int> final)  {
    if (final.first >= MAXCELL) return false;
    if (final.second >= MAXCELL) return false;

    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds

    if (initial.first == final.first && initial.second == final.second) return false;

    int start, end;

    // move horizontally
    if (initial.first == final.first) {
        start = final.second < initial.second ? final.second : initial.second;
        end = final.second < initial.second ? initial.second : final.second;

        pair<int, int> tmp = make_pair(final.first, start);
        for (int i = start + 1; i < end; ++i) {
            tmp.second = i;
            if (i != initial.second && getTheBoard()->hasObstacle(tmp)) return false;
        }

        return !getTheBoard()->hasAlly(getColour(), final);
    }
    // move vertically
    else if (initial.second == final.second) {
        start = final.first < initial.first ? final.first : initial.first;
        end = final.first < initial.first ? initial.first : final.first;

        pair<int, int> tmp = make_pair(start, final.second);
        for (int i = start + 1; i < end; ++i) {
            tmp.first = i;
            if (i != initial.first && getTheBoard()->hasObstacle(tmp)) return false;
        }

        return !getTheBoard()->hasAlly(getColour(), final);
    }
    
    return false;
}

vector<pair<int, int>> Rook::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
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
    return moves;
}

PieceName Rook::getType() {return PieceName::Rook;}
