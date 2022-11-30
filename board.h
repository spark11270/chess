#ifndef BOARD_H
#define BOARD_H
#include <string.h>
#include "piece.h"
#include "cell.h"

class Board : public Subject {
    std::vector<std::vector<Cell>> theBoard;
    bool whosTurn; // true if white's turn and false if black's turn

public:
    Board();
    void move(std:string initial, std::string fianl);
    void promote(std::string initial, std::string final, char promto);
    bool isWhiteTurn();
    
    // We probably won't have render 
    // Instead use ostream operator to display the board 
    // It's just there so that I get test if textdisplay is working
    void render();
    Cell getCell(int row, int col); 



};

#endif
