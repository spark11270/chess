#include "knight.h"

using namespace std;

Knight::Knight(Colour c, int row, int col, Board *theBoard) : Piece(c, row, col, PieceName::Knight, theBoard) {}

bool Knight::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position
    if (((initial.first + 2) == final.first) && (((initial.second + 1) == final.second) || ((initial.second - 1) == final.second))) return true; 
    if (((initial.first - 2) == final.first) && (((initial.second + 1) == final.second) || ((initial.second - 1) == final.second))) return true;
    if (((initial.second - 2) == final.second) && (((initial.first + 1) == final.first) || ((initial.first - 1) == final.first))) return true;
    if (((initial.second + 2) == final.second) && (((initial.first + 1) == final.first) || ((initial.first - 1) == final.first))) return true;
    if (initial.second == final.second) return true; //move vertically
    return false;
}

vector<pair<int, int>> Knight::getPosMoves() {
    vector<pair<int, int>> moves;
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second + 2));
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second - 2));
    moves.push_back(make_pair(getCoords().first - 1, getCoords().second + 2));
    moves.push_back(make_pair(getCoords().first - 1, getCoords().second - 2));
    moves.push_back(make_pair(getCoords().first + 2, getCoords().second + 1));
    moves.push_back(make_pair(getCoords().first + 2, getCoords().second - 1));
    moves.push_back(make_pair(getCoords().first - 2, getCoords().second + 1));
    moves.push_back(make_pair(getCoords().first - 2, getCoords().second - 1));
    return moves;
}

PieceName Knight::getType() {return PieceName::Knight;}
