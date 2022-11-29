#include "piece.h"
using namespace std;


Piece::Piece(Colour color, int row, int col) : type{getType()}, colour{colour}, row{row}, col{col}, isFirstMove{false} {}

int Piece::getRow() {return row;}

int Piece::getColumn() {return col;}

Colour Piece::getColour() {return colour;}
