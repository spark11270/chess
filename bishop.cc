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
    pair<int, int> xyCoords = make_pair(initial.first, initial.second);

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
