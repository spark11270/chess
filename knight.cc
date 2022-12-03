#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(Colour c, int row, int col, Board *theBoard) : Piece(c, row, col, PieceName::Knight, theBoard) {}

bool Knight::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    
    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds

    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    // my own item?
    if (getTheBoard()->hasAlly(getColour(), final)) return false;
    
    if (((initial.first + 2) == final.first) && (((initial.second + 1) == final.second) || ((initial.second - 1) == final.second))) return true; 
    if (((initial.first - 2) == final.first) && (((initial.second + 1) == final.second) || ((initial.second - 1) == final.second))) return true;
    if (((initial.second - 2) == final.second) && (((initial.first + 1) == final.first) || ((initial.first - 1) == final.first))) return true;
    if (((initial.second + 2) == final.second) && (((initial.first + 1) == final.first) || ((initial.first - 1) == final.first))) return true;
    if (initial.second == final.second) return true; //move vertically

    return false;
}

vector<pair<int, int>> Knight::getPosMoves() {
    vector<pair<int, int>> moves;

    pair<int, int> pos;
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second + 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second - 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second + 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second - 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first + 2;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first + 2;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 2;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 2;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    return moves;
}

PieceName Knight::getType() {return PieceName::Knight;}
