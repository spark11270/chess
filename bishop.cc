#include "bishop.h"
#include "board.h"

using namespace std;

Bishop::Bishop(Board *b, Colour c, int row, int col) : Piece{b, c, PieceName::Bishop, row, col} {}

bool Bishop::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    
    // check if move is out of bounds
    if (outOfBounds(initial, final)) return false;

    // check if moves diagonally     
    if (abs(final.second - initial.second) != abs(final.first - initial.first)) return false;

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

vector<pair<int, int>> Bishop::getPosMoves() {
    
    vector<pair<int, int>> moves;

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
