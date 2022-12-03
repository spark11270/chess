#include "king.h"
#include "board.h"

using namespace std;

King::King(Colour c, int row, int col, Board *theBoard) : Piece(c, row, col, PieceName::King, theBoard) {}

bool King::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds

    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    if (((initial.first + 1) == final.first || (initial.first - 1) == final.first) && 
        ((initial.second + 1) == final.second || (initial.second - 1) == final.second)) return true; // check diagnoals

    if ((initial.first == final.first) && ((initial.second + 1) == final.second || (initial.second - 1) == final.second)) return true; // moves left and right one square
    if ((initial.second == final.second) && ((initial.first + 1 == final.first) || initial.first - 1 == final.first)) return true; // moves up and down one square

    // my own item?
    if (getTheBoard()->hasAlly(getColour(), final)) return false;

    return false;
}

vector<pair<int, int>> King::getPosMoves() {
    vector<pair<int, int>> moves;
    // vertical
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second));
    moves.push_back(make_pair(getCoords().first - 1, getCoords().second));
    // horizontal
    moves.push_back(make_pair(getCoords().first, getCoords().second + 1));
    moves.push_back(make_pair(getCoords().first, getCoords().second - 1));
    // forward diagonal
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second - 1));
    moves.push_back(make_pair(getCoords().first - 1, getCoords().second + 1));
    // backward diagonal
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second + 1));
    moves.push_back(make_pair(getCoords().first - 1, getCoords().second - 1));
    return moves;
}

PieceName King::getType() {return PieceName::King;}
