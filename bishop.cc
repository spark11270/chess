#include "bishop.h"
#include "board.h"

using namespace std;

Bishop::Bishop(Colour c, int row, int col, Board *theBoard) : Piece(c, row, col, PieceName::Bishop, theBoard) {}

bool Bishop::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    int x = 1;
    int y = 1;
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds

    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds;
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position
 
    // check is there is an ally in the final destination
    if (getTheBoard()->hasAlly(getColour(), final)) return false;
    // check if moves diagnoally     
    if (abs(final.second - initial.second) != abs(final.first - initial.first)) return false; 
    // check if there is an obstacle on the way

    if ((final.second - initial.second) < 0) {
        // moves in negative x direction
        x = -1;
    }
    if ((final.first - initial.first) < 0) {
        // moives in negative y direction
        y = -1;
    }

    pair<int, int> dir = make_pair(y, x); // y = row && x = column
    pair<int, int> xyCoords = make_pair(initial.first, initial.first);

    for (int i = 1; i < abs(final.second - initial.second); ++i) {
        xyCoords.first += dir.first;
        xyCoords.second += dir.second;
        if(getTheBoard()->hasObstacle(xyCoords)) return false;
    }
    return true;
}

vector<pair<int, int>> Bishop::getPosMoves() {
    vector<pair<int, int>> moves;

    // for (int i = 0; i < MAXCELL; i++) {
    //     for (int j = 0; j < MAXCELL; j++) {
    //         if ((i - getCoords().first == j - getCoords().second) || (i - getCoords().first == -(j - getCoords().second))) {
    //             if (i != getCoords().first && j!= getCoords().second) {
    //                 pair<int, int> pos = make_pair(i, j);
    //                 if (isValidMove(getCoords(), pos)) {
    //                     moves.push_back(pos);
    //                 }
    //             }
    //         } 
    //     }
    // }

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

PieceName Bishop::getType() {return PieceName::Bishop;}
