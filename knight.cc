#include "knight.h"

using namespace std;

Knight::Knight(Colour c, int row, int col) : Piece(c, row, col, PieceName::Knight) {}

bool Knight::isValidMove(int initialRow, int initialCol, int finalRow, int finalCol, bool isFirstMove) {
    if (finalRow >= MAXCELL) return false; // check out of bounds
    if (finalCol >= MAXCELL) return false; // check out of bounds
    if ((initialRow == finalRow) && (initialCol == finalCol)) return false; // you cannot stay in the same position
    if (((initialRow + 2) == finalRow) && (((initialCol + 1) == finalCol) || ((initialCol - 1) == finalCol))) return true; 
    if (((initialRow - 2) == finalRow) && (((initialCol + 1) == finalCol) || ((initialCol - 1) == finalCol))) return true;
    if (((initialCol - 2) == finalCol) && (((initialRow + 1) == finalRow) || ((initialRow - 1) == finalRow))) return true;
    if (((initialCol + 2) == finalCol) && (((initialRow + 1) == finalRow) || ((initialRow - 1) == finalRow))) return true;
    if (initialCol == finalCol) return true; //move vertically
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
