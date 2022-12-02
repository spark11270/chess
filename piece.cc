#include "piece.h"
using namespace std;

Piece::Piece(Colour colour, int row, int col, PieceName type) : colour{colour}, coords{make_pair(row, col)}, type{type} {}

pair<int, int> Piece::getCoords() {return coords;}

void Piece::setCoords(int r, int c) {
    coords = make_pair(r, c);
}

void Piece::modifyCoords(pair<int,int> &newCoords) {
    coords.first = newCoords.first;
    coords.second = newCoords.second;
}

Colour Piece::getColour() {return colour;}

Piece::~Piece() {};
