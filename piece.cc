#include "piece.h"
#include "board.h"

using namespace std;

Piece::Piece(Board *b, Colour c, PieceName type, int row, int col) : b{b}, colour{c}, type{type}, isFirstMove{true}, coords{make_pair(row, col)} {}


bool Piece::outOfBounds(pair<int,int> initial, pair<int,int> final) {

    // check bounds
    if (final.first >= MAXCELL) return true;
    if (final.second >= MAXCELL) return true;
    if (final.first < 0) return true;
    if (final.second < 0) return true;

    // must not move to the same spot
    if (initial.first == final.first && initial.second == final.second) return true;

    // check if the last position contains one of the player's pieces
    if (b->hasAlly(colour, final)) return true;

    return false;

}


Board *Piece::getTheBoard() {return b;}


Colour Piece::getColour() {return colour;}


bool Piece::getIsFirstMove() {return isFirstMove;}


pair<int, int> Piece::getCoords() {return coords;}


void Piece::setIsFirstMove() {
    isFirstMove = false;
}


void Piece::modifyCoords(pair<int,int> newCoords) {
    coords.first = newCoords.first;
    coords.second = newCoords.second;
}


Piece::~Piece() {};
