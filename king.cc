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

    // my own item?
    if (getTheBoard()->hasAlly(getColour(), final)) return false;

    if (getTheBoard()->canCastle(initial, final)) {
        // checks if king moves 2 square vertically
        if ((abs(initial.first - final.first) == 2) && (initial.second == final.second)) return true;
        // checks if king moves 2 square horizontally
        if ((abs(initial.second - final.second) == 2) && (initial.first = final.first)) return true;
        return false;
    }

    if (((initial.first + 1) == final.first || (initial.first - 1) == final.first) && 
        ((initial.second + 1) == final.second || (initial.second - 1) == final.second)) return true; // check diagnoals

    if ((initial.first == final.first) && ((initial.second + 1) == final.second || (initial.second - 1) == final.second)) return true; // moves left and right one square
    if ((initial.second == final.second) && ((initial.first + 1 == final.first) || initial.first - 1 == final.first)) return true; // moves up and down one square

    return false;
}

vector<pair<int, int>> King::getPosMoves() {
    vector<pair<int, int>> moves;

    // vertical
    pair<int, int> pos;
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // horizontal
    pos.first = getCoords().first;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // forward diagonal
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // backward diagonal
    pos.first = getCoords().first + 1;
    pos.second = getCoords().second + 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }
    pos.first = getCoords().first - 1;
    pos.second = getCoords().second - 1;
    if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
    }

    // move up 2 squares
    pos.first = getCoords().first + 2;
    pos.second = getCoords().second;
    if (isValidMove(getCoords(), pos)) {
        moves.push_back(pos);
    }

    // move down 2 squares
    pos.first = getCoords().first - 2;
    pos.second = getCoords().second;
    if (isValidMove(getCoords(), pos)) {
        moves.push_back(pos);
    }

    // move right 2 squares
    pos.first = getCoords().first;
    pos.second = getCoords().second + 2;
    if (isValidMove(getCoords(), pos)) {
        moves.push_back(pos);
    }

    // move left 2 squares
    pos.first = getCoords().first;
    pos.second = getCoords().second - 2;
    if (isValidMove(getCoords(), pos)) {
        moves.push_back(pos);
    }

    return moves;
}

PieceName King::getType() {return PieceName::King;}
