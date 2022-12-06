#include "knight.h"
#include "board.h"

using namespace std;

Knight::Knight(shared_ptr<Board> b, Colour c, int row, int col) : Piece{b, c, PieceName::Knight, row, col} {}


bool Knight::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    
    if (outOfBounds(initial, final)) return false;
    
    if ((abs(final.first - initial.first) == 2) && (abs(final.second - initial.second) == 1)) return true;
    if ((abs(final.second - initial.second) == 2) && (abs(final.first - initial.first) == 1)) return true;

    return false;
}


vector<pair<int, int>> Knight::getPosMoves() {
    
    vector<pair<int, int>> moves;
    pair<int, int> pos;

    // 2 right, 1 down
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second + 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 2 right, 1 up
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second + 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 2 left, 1 down
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second - 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 2 left, 1 up
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second - 2;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 1 right, 2 down
    pos.first = getCoords().first + 2;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 1 right, 2 up
    pos.first = getCoords().first - 2;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 1 left, 2 down
    pos.first = getCoords().first + 2;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // 1 left, 2 up
    pos.first = getCoords().first - 2;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    return moves;
}

PieceName Knight::getType() {return PieceName::Knight;}
