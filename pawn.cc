#include "pawn.h"
#include "board.h"

using namespace std;

Pawn::Pawn(shared_ptr<Board> b, Colour c, int row, int col) : Piece{b, c, PieceName::Pawn, row, col} {}


bool Pawn::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {

    shared_ptr<Board> b = getTheBoard();
    Colour curr = getColour();

    // check if move is out of bounds
    if (outOfBounds(initial, final)) return false;

    // white pieces only move up
    if (((curr) == Colour::White) && (initial.first < final.first)) return false;

    // black pieces only move down
    if ((curr == Colour::Black) && (initial.first > final.first)) return false;

    // forwards
    if (initial.second == final.second) {
        // cannot capture opponent going forwards
        if (b->hasOpponent(curr, final)) return false;
        // if first move
        if (getNumMoves() == 0) {
            if (abs(final.first - initial.first) == 2) return true;
        }
        // does not move forward by 1
        if (abs(final.first - initial.first) != 1) return false;
        return true;
    } 
    // diagonal
    else {
        // does not move diagonally by 1
        if ((abs(final.first - initial.first) != 1) || (abs(final.second - initial.second) != 1)) return false;
        // can capture
        if (b->hasOpponent(curr, final)) return true;
        // can enpassant
        if (b->canEP(initial, final)) return true;
        return false;
    }
}


vector<pair<int, int>> Pawn::getPosMoves() {

    vector<pair<int, int>> moves;
    pair<int, int> init = getCoords();
    Colour curr = getColour();

    // black moves down
    if (curr == Colour::Black) {
        // single move forward
        pair<int, int> pos = make_pair(init.first + 1, init.second);
        if (isValidMove(init, pos)) {
            moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getNumMoves() == 0) { 
            pos = make_pair(init.first + 2, init.second);
            if (isValidMove(init, pos)) {
                moves.push_back(pos);
            }
        }
        pos = make_pair(init.first + 1, init.second - 1);
        if (isValidMove(init, pos)) {
            moves.push_back(pos);
        }
        pos.second = init.second + 1;
        if (isValidMove(init, pos)) {
            moves.push_back(pos);
        }
    // white moves up
    } else {
        // single move forward
        pair<int, int> pos;
        pos = make_pair(init.first - 1, init.second);
        if (isValidMove(init, pos)) {
             moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getNumMoves() == 0) { 
            pos = make_pair(init.first - 2, init.second);
            if (isValidMove(init, pos)) {
                moves.push_back(pos);
            }
        }
        pos = make_pair(init.first - 1, init.second - 1);
        if (isValidMove(init, pos)) {
            moves.push_back(pos);
        }
        pos.second = init.second + 1;
        if (isValidMove(init, pos)) {
            moves.push_back(pos);
        }
    }
    return moves;
}


PieceName Pawn::getType() {return PieceName::Pawn;}