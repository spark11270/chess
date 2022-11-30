#include "board.h"
#include "cell.h"
#include "iostream"
#include <vector>

Board::Board() {
    for (int i = 0; i < 8; i++) {
        std::vector<Cell> row;
  
        for (int j = 0; j < 8; j++) {
            if (!((i + j) % 2)) {
                row.emplace_back(Cell(i, j, this));
            } else {
                row.emplace_back(Cell(i, j, this));
            }
        }
        theBoard.emplace_back(row);
    }
}

void Board::render() {
    notifyObservers();
}

Cell Board::getCell(int row, int col) {
    return theBoard[row][col];
}
