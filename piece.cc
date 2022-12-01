#include "piece.h"
using namespace std;

Piece::Piece(Colour colour, int row, int col) : colour{colour}, row{row}, col{col} {}

int Piece::getRow() {return row;}

int Piece::getColumn() {return col;}

Colour Piece::getColour() {return colour;}
