#include <utility>

#include "rook.h"
#include "board.h"

using namespace std;

Rook:: Rook(Board *b, Colour c, int row, int col) : Piece{b, c, PieceName::Rook, row, col} {}


bool Rook::isValidMove(std::pair<int, int> initial, std::pair<int, int> final)  {

    // check if move is out of bounds
    if (outOfBounds(initial, final)) return false;

    int start, end;

    // horizontal
    if (initial.first == final.first) {

        // set start and end column based on position
        start = final.second < initial.second ? final.second : initial.second;
        end = final.second < initial.second ? initial.second : final.second;
        pair<int, int> tmp = make_pair(final.first, start);

        // check every position the piece moves in for obstacles
        for (int i = start + 1; i < end; ++i) {
            tmp.second = i;
            if (i != initial.second && getTheBoard()->hasObstacle(tmp)) return false;  
        }

        return true;
    }
    // vertical
    else if (initial.second == final.second) {

        // set start and end row based on position
        start = final.first < initial.first ? final.first : initial.first;
        end = final.first < initial.first ? initial.first : final.first;
        pair<int, int> tmp = make_pair(start, final.second);

        // check every position the piece moves in for obstacles
        for (int i = start + 1; i < end; ++i) {
            tmp.first = i;
            if (i != initial.first && getTheBoard()->hasObstacle(tmp)) return false;
        }

        return true;
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

        // return column excluding the rook
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

         // return row excluding the rook
        if (j != getCoords().second) {
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
    }

    return moves;
}


PieceName Rook::getType() {return PieceName::Rook;}
