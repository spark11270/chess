#include "piece.h"

using namespace std;

Piece::Piece(Colour colour, int row, int col, PieceName type, Board *theBoard) : colour{colour}, coords{make_pair(row, col)}, type{type}, theBoard{theBoard} {}

pair<int, int> Piece::getCoords() {return coords;}

void Piece::setCoords(int r, int c) {
    coords = make_pair(r, c);
}

void Piece::modifyCoords(pair<int,int> &newCoords) {
    coords.first = newCoords.first;
    coords.second = newCoords.second;
}

Colour Piece::getColour() {return colour;}

bool Piece::isMine(Piece *p) {
    if (p != null && p->getColour() == getColour()) {
        return true;
    }
    return false;
}

Piece::~Piece() {};
