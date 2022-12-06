#include "king.h"
#include "board.h"

using namespace std;

King::King(shared_ptr<Board> b, Colour c, int row, int col) : Piece{b, c, PieceName::King, row, col} {}

bool King::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {

    if (outOfBounds(initial, final)) return false;

    if (getTheBoard()->canCastle(initial, final) != ' ') {
        return true;
    }

    // vertical
    if ((initial.first == final.first) && (abs(final.second - initial.second) == 1)) return true;

    // horizontal
    if ((initial.second == final.second) && (abs(final.first - initial.first) == 1)) return true; 

    // diagonal
    if ((abs(final.second - initial.second) == 1) && (abs(final.first - initial.first) == 1)) return true;

    return false;
}


vector<pair<int, int>> King::getPosMoves() {
    vector<pair<int, int>> moves;
    pair<int, int> init = getCoords();
    // vertical
    pair<int, int> pos = make_pair(init.first + 1, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first - 1, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // horizontal
    pos = make_pair(init.first, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // backward diagonal
    pos = make_pair(init.first + 1, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first - 1, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // forward diagonal
    pos = make_pair(init.first - 1, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first + 1, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // move up 2 squares
    pos = make_pair(init.first + 2, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // move left 2 squares
    pos = make_pair(init.first, init.second - 2);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // move down 2 squares
    pos = make_pair(init.first - 2, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    // move right 2 squares
    pos = make_pair(init.first, init.second + 2);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    
    return moves;
}

PieceName King::getType() {return PieceName::King;}
