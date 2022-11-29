#include "piece.h"
using namespace std;


Piece::Piece(PieceName type, Color color, int row, int col) : type{type}, color{color}, row{row}, col{col}, isFirstMove{false} {}

PieceName Piece::getType() {return type;}

int Piece::getRow() {return row;}

int Piece::getColumn() {return col;}

Color Piece::getColor() {return color;}
