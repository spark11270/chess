#include "cell.h"

using namespace std;

Cell::Cell(int row, int col, Board *board, Piece *piece) : row{row}, col{col}, board{board}, piece{piece} {}
    
void Cell::addPiece(Piece *p) {
    piece = p;
}

void Cell::removePiece() {
    piece = nullptr;
}

int Cell::getRow() {
    return row;
}

int Cell::getCol() {
    return col;
}

Cell::~Cell() {}
