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
	int m = 0;
	int n = 0;
	if (board->getTotalMoves().size()) {
		m = board->getTotalMoves().back().from.first;
		n = board->getTotalMoves().back().from.second;
		std::cout << m << std::endl;
		std::cout << n << std::endl;
	}
	for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) { 
				Colour c = board->getBoard()[i][j]->getColour();
				if (m && n) {
					if ((m+n) % 2) {
						w->fillRectangle(50*(n+1), 50*m, 50, 50, 1);
					} else {
						w->fillRectangle(50*(n+1), 50*m, 50, 50, 0);
					}
				}
				if (c == Colour::Black) {
					w->drawBigString(65+j*50, i*50+35, printPiece(board->getBoard()[i][j]->getType()), 4);
				} else {
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
