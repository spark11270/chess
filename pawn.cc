#include "pawn.h"
#include "board.h"

using namespace std;

Pawn::Pawn(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Pawn, theBoard} {}

bool Pawn::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    
    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position
   
    // can move 2 square forwards only if first move
    if (abs(initial.first - final.first) == abs(initial.second - final.second) && abs(initial.second - final.second) == 1) {
        // move diagonally

        // if trying to capture
        if (getTheBoard()->hasObstacle(final)) return true;

        // if trying to enpassant
        if ((getTheBoard()->hasObstacle(final) == false) && (getTheBoard()->hasOpponent(getColour(), make_pair(initial.first, final.second))) && 
            (getTheBoard()->canEP(initial, final))) {
        if ((getTheBoard()->hasObstacle(final) == false) && (getTheBoard()->hasOpponent(getColour(), make_pair(initial.first, final.second))) && 
            (getTheBoard()->canEP((getTheBoard()->getPieceAt(make_pair(initial.first, final.second))), initial, final))) {
                return true;
            }
    }

    if (getIsFirstMove() == true) { 
        if(getColour() == Colour::Black) {
            if ((initial.first + 2) == final.first) return true;
        } else {
            if ((initial.first - 2) == final.first) return true;
        }
        
    }
    if (getColour() == Colour::Black) {
        if ((initial.first + 1) == final.first) return true;
    } else {
        if ((initial.first - 1) == final.first) return true;
    }

    // my own item?
    if (getTheBoard()->hasAlly(getColour(), final)) return false;

    return false;
}

vector<pair<int, int>> Pawn::getPosMoves() {
    vector<pair<int, int>> moves;

    // black moves down
    if (getColour() == Colour::Black) {
        // single move forward
        pair<int, int> pos;
        pos.first = getCoords().first + 1;
        pos.second = getCoords().second;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getIsFirstMove() == true) { 
            pos.first = getCoords().first + 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
        pos.first = getCoords().first - 1;
        pos.second = getCoords().second - 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
        pos.second = getCoords().second + 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
    // white moves up
    } else {
        // single move forward
        pair<int, int> pos;
        pos.first = getCoords().first - 1;
        pos.second = getCoords().second;
        if (isValidMove(getCoords(), pos)) {
             moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getIsFirstMove() == true) { 
            pos.first = getCoords().first - 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
        pos.first = getCoords().first - 1;
        pos.second = getCoords().second - 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
        pos.second = getCoords().second + 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
    }
    return moves;
}

PieceName Pawn::getType() {return PieceName::Pawn;}
