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
	for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) { 
				Colour c = board->getBoard()[i][j]->getColour();
				if (from_x && from_y) {
					if ((from_x+from_y) % 2) {
						w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 1);
					} else {
						w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 0);
					}
				}
			/*	
				if (to_x && to_y) {
                                                if ((to_x+to_y) % 2) {
                                                        w->fillRectangle(50*(to_y), 50*to_x, 50, 50, 1);
                                                } else {
                                                        w->fillRectangle(50*(to_y+1), 50*to_x, 50, 50, 0);
                                                }
                                        }
					*/
				if (c == Colour::Black) {
					if ((i+j) % 2) {
                                                        w->fillRectangle(50*(j+1), 50*i, 50, 50, 1);
                                                } else {
                                                    	w->fillRectangle(50*(j+1), 50*i, 50, 50, 0);
                                                }

					w->drawBigString(65+j*50, i*50+35, printPiece(board->getBoard()[i][j]->getType()), 4);
				} else {
                                		if ((i+j) % 2) {
                                        		w->fillRectangle(50*(j+1), 50*i, 50, 50, 1);
                                		} else {
                                        		w->fillRectangle(50*(j+1), 50*i, 50, 50, 0);
                                		}
					w->drawBigString(65+j*50, i*50+35, printPiece(board->getBoard()[i][j]->getType()), 3);
				}


			}
		}
	}
}

// Detach for deleting
GraphicsDisplay::~GraphicsDisplay() {
        board->detach(this);
}
