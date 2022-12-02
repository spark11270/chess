#include "pawn.h"

using namespace std;

Pawn::Pawn(Colour c, int row, int col) : Piece{c, row, col, PieceName::Pawn} {}

bool Pawn::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds

    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    if (isFirstMove == true) { // can move 2 square forwards only if first move
        if ((initial.first + 2) == final.first) return true;
    }

    if ((initial.first + 1) == final.first) return true;
    
    return false;
}

vector<pair<int, int>> Pawn::getPosMoves() {
    vector<pair<int, int>> moves;
    moves.push_back(make_pair(getCoords().first + 1, getCoords().second));
    if (isFirstMove == true) { // can move 2 square forwards only if first move
        moves.push_back(make_pair(getCoords().first + 2, getCoords().second));
    }
    return moves;
}

PieceName Pawn::getType() {return PieceName::Pawn;}
