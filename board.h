#ifndef BOARD_H
#define BOARD_H
#include <string.h>
#include "piece.h"
#include "cell.h"

class Board {
    std::vector<std::vector<Cell>> theBoard;
    bool whosTurn; // true if white's turn and false if black's turn

public:
    void move(std:string initial, std::string fianl);
    void promote(std::string initial, std::string final, char promto);
    bool isWhiteTurn();



};

#endif
