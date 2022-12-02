#include "piece.h"
using namespace std;

Piece::Piece(Colour colour, int row, int col) : colour{colour}, coords{make_pair(row, col)} {}

pair<int, int> Piece::getCoords() {return coords;}

void Piece::setCoords(int r, int c) {
    coords = make_pair(r, c);
}

Colour Piece::getColour() {return colour;}
