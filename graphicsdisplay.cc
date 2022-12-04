#include "graphicsdisplay.h"
#include "board.h"
#include "xwindow.h"
#include <string>

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
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) { 
				Colour c = board->getBoard()[i][j]->getColour();
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
