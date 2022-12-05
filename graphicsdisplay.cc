#include "graphicsdisplay.h"
#include "board.h"
#include "xwindow.h"
#include <string>
#include <iostream>

// Adds graphicsdisplay observer to the subject
GraphicsDisplay::GraphicsDisplay(Board* board) : board{board} {
        w = new Xwindow(450, 450);
        w->drawBoard();
        board->attach(this);
}

std::string printPiece(PieceName n) {
        if (n == PieceName::King) {
            return "K";
        } else if (n == PieceName::Queen) {
            return "Q";
        } else if (n == PieceName::Bishop) {
            return "B";
        } else if (n == PieceName::Rook) {
            return "R";
        } else if (n == PieceName::Knight) {
            return "N";
        } else if (n == PieceName::Pawn) {
            return "P";
        }
    }


// Renders the board to the interface
void GraphicsDisplay::notify() {
	int from_x = 0;
	int from_y = 0;
	int to_x = 0;
        int to_y = 0;
	if (board->getTotalMoves().size()) {
		from_x = board->getTotalMoves().back().from.first;
		from_y = board->getTotalMoves().back().from.second;
		to_x = board->getTotalMoves().back().to.first;
                to_y = board->getTotalMoves().back().to.second;
	}
	std::cout << from_x << from_y << std::endl;
	std::cout << to_x << to_y << std::endl;
	for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) { 
				Colour c = board->getBoard()[i][j]->getColour();
				if (board->getTotalMoves().size()) {
					if ((from_x+from_y) % 2) {
						w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 1);
					} else {
						w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 0);
					}
				}
		/*	
				if (board->getTotalMoves().size()) {
                                                if ((to_x+to_y) % 2) {
                                                        w->fillRectangle(50*(to_y+1), 50*to_x, 50, 50, 1);
                                                } else {
                                                        w->fillRectangle(50*(to_y+1), 50*to_x, 50, 50, 0);
                                                }
                                        }
		*/			
				if (c == Colour::Black) {
					if (to_y == j && to_x == i){
					if ((i+j) % 2) {
                                                        w->fillRectangle(50*(j+1), 50*i, 50, 50, 1);
                                                } else {
                                                    	w->fillRectangle(50*(j+1), 50*i, 50, 50, 0);
                                                }
					}
					w->drawBigString(65+j*50, i*50+35, printPiece(board->getBoard()[i][j]->getType()), 4);
				} else {
					if (to_y == j && to_x == i){
                                  		if ((i+j) % 2) {
                                        		w->fillRectangle(50*(j+1), 50*i, 50, 50, 1);
                                		} else {
                                        		w->fillRectangle(50*(j+1), 50*i, 50, 50, 0);
                                		}
						}
					w->drawBigString(65+j*50, i*50+35, printPiece(board->getBoard()[i][j]->getType()), 3);
				}


			}
			if (board->getBoard()[0][0] == nullptr) {
				w->fillRectangle(50*(0+1), 50*0, 50, 50, 0);
			}
			if (board->getBoard()[7][7] == nullptr) {
                                w->fillRectangle(50*(7+1), 50*7, 50, 50, 0);
                        }
			if (board->getBoard()[0][7] == nullptr) {
                                w->fillRectangle(50*(7+1), 50*0, 50, 50, 1);
                        }
			if (board->getBoard()[7][0] == nullptr) {
                                w->fillRectangle(50*(0+1), 50*7, 50, 50, 1);
                        }
		}
	}
}

// Detach for deleting
GraphicsDisplay::~GraphicsDisplay() {
        board->detach(this);
}
