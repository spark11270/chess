#include "pawn.h"
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
    if (isMine(theBoard->getBoard()[final.first][final.second] != nullptr)) return false;

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

void Pawn::setIsFirstMove() {
    isFirstMove = false;
}

PieceName Pawn::getType() {return PieceName::Pawn;}
