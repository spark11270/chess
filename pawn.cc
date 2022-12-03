#include "pawn.h"
#include "board.h"
#include <iostream>
using namespace std;

Pawn::Pawn(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Pawn, theBoard}, isFirstMove{true} {}

bool Pawn::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    
    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position
   
    // can move 2 square forwards only if first move
    if (isFirstMove == true) { 
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
        if (isFirstMove == true) { 
            pos.first = getCoords().first + 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
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
        if (isFirstMove == true) { 
            pos.first = getCoords().first - 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
    }
    return moves;
}

void Pawn::setIsFirstMove() {
    isFirstMove = false;
}

PieceName Pawn::getType() {return PieceName::Pawn;}
