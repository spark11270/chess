#include "board.h"
#include "piece.h"
#include "iostream"
#include <vector>
#include "colour.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

// Initialze the board for game. We may need an empty board for setup mode
// Note that the cells with no pieces are uninitialized. 
Board::Board() {
    // Place Black Pieces on Board
    theBoard[0][0] = new Rook(Colour::Black, 0, 0);
    theBoard[0][7] = new Rook(Colour::Black, 0, 7);
    theBoard[0][1] = new Knight(Colour::Black, 0, 1);
    theBoard[0][6] = new Knight(Colour::Black, 0, 6);
    theBoard[0][2] = new Bishop(Colour::Black, 0, 2);
    theBoard[0][5] = new Bishop(Colour::Black, 0, 5);
    theBoard[0][3] = new Queen(Colour::Black, 0, 3);
    theBoard[0][4] = new King(Colour::Black, 0, 4);
    for (int i = 1; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            theBoard[i][j] = new Pawn(Colour::Black, i, j);
        }
    }

    // Place White Pieces on Board
    theBoard[7][0] = new Rook(Colour::White, 0, 0);
    theBoard[7][7] = new Rook(Colour::White, 0, 7);
    theBoard[7][1] = new Knight(Colour::White, 0, 1);
    theBoard[7][6] = new Knight(Colour::White, 0, 6);
    theBoard[7][2] = new Bishop(Colour::White, 0, 2);
    theBoard[7][5] = new Bishop(Colour::White, 0, 5);
    theBoard[7][3] = new Queen(Colour::White, 0, 3);
    theBoard[7][4] = new King(Colour::White, 0, 4);
    for (int i = 6; i < 7; i++) {
        for (int j = 0; j < 8; j++) {
            theBoard[i][j] = new Pawn(Colour::White, i, j);
        }
    }

    // ***** Create Empty Board *****
    /*
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            theBoard[i][j] = nullptr;
    }
    */
}

void Board::render() {
    notifyObservers();
}

Piece* Board::getPiece(int row, int col) {
    return theBoard[row][col];
}
