#include "pawn.h"

using namespace std;

Pawn::Pawn(Colour c, int row, int col) : Piece{c, row, col} {}

bool Pawn::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds

    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position

    if (isFirstMove == true) { // can move 2 square forwards only if first move
        if ((initialRow + 2) == finalRow) return true;
    }

    if ((initialRow + 1) == finalRow) return true;
    
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

PieceName Pawn::getType() {return PieceName::pawn;}
