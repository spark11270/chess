#ifndef BOARD_H
#define BOARD_H
#include <string.h>
#include "piece.h"
#include "subject.h"

class Board : public Subject {
    // I've changed theBoard to a matrix of Pieces 
    // instead of a vector of vectors. Think this is easier to implement
    // But feel free to change it back if required
    Piece* theBoard[8][8];
    bool whosTurn; // true if white's turn and false if black's turn

public:
    Board();

    void move(std::string initial, std::string final);
    void promote(std::string initial, std::string final, char promto);
    bool isWhiteTurn();

    void render();
    Piece* getPiece(int row, int col); 



};

#endif
