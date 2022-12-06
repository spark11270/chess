#include "queen.h"
#include "board.h"

using namespace std;

Queen::Queen(Board *b, Colour c, int row, int col) : Piece{b, c, PieceName::Queen, row, col} {}


bool Queen::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {

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
    // diagonal
    else if (abs(final.second - initial.second) == abs(final.first - initial.first)) {

        int x = 1;
        int y = 1;

        // moves in negative x direction
        if ((final.second - initial.second) < 0) {x = -1;}

        // moves in negative y direction
        if ((final.first - initial.first) < 0) {y = -1;}
        
        // y = row && x = column
        pair<int, int> dir = make_pair(y, x);
        pair<int, int> xyCoords = make_pair(initial.first, initial.second);
        
        // check every position the piece moves in for obstacles
        for (int i = 1; i < abs(final.second - initial.second); ++i) {
            xyCoords.first += dir.first;
            xyCoords.second += dir.second;
            if(getTheBoard()->hasObstacle(xyCoords)) return false;
        }
        
        return true;
    }

    return false;
}


vector<pair<int, int>> Queen::getPosMoves() {

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

    // diagonal
    pair<int, int> coord1 = make_pair(1, 1);
    pair<int, int> coord2 = make_pair(1, -1);
    pair<int, int> coord3 = make_pair(-1, -1);
    pair<int, int> coord4 = make_pair(-1, 1);
    
    pair<int, int> pos1 = make_pair(getCoords().first, getCoords().second);
    pair<int, int> pos2 = make_pair(getCoords().first, getCoords().second);
    pair<int, int> pos3 = make_pair(getCoords().first, getCoords().second);
    pair<int, int> pos4 = make_pair(getCoords().first, getCoords().second);

    for (int i = getCoords().first; i < MAXCELL; ++i) {
        // check when both x and y are positive
        pos1.first += coord1.first;
        pos1.second += coord1.second;
        if (isValidMove(getCoords(), pos1)) {
            moves.push_back(pos1);
        }

        // check when x is negative and y is positive
        pos2.first += coord2.first;
        pos2.second += coord2.second;
        if (isValidMove(getCoords(), pos2)) {
            moves.push_back(pos2);
        }

        // check when x and y are negative
        pos3.first += coord3.first;
        pos3.second += coord3.second;
        if (isValidMove(getCoords(), pos3)) {
            moves.push_back(pos3);
        }

        // check when x is positive and y is negative
        pos4.first += coord4.first;
        pos4.second += coord4.second;
        if (isValidMove(getCoords(), pos4)) {
            moves.push_back(pos4);
        }
    }

    return moves;
}


PieceName Queen::getType() {return PieceName::Queen;}
