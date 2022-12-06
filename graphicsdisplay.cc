#include "graphicsdisplay.h"
#include "board.h"
#include "xwindow.h"
#include <string>
#include <iostream>
#include <cstring>

// Adds graphicsdisplay observer to the subject
GraphicsDisplay::GraphicsDisplay(Board* board) : board{board} {
        w = new Xwindow(450, 450);
	w->drawBoard();
        board->attach(this);
}

// Helper for getting bitmap file name
std::string printPiece(PieceName n, Colour c) {
    if (c == Colour::White) {
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
    } else {
        if (n == PieceName::King) {
            return "k";
        } else if (n == PieceName::Queen) {
            return "q";
        } else if (n == PieceName::Bishop) {
            return "b";
        } else if (n == PieceName::Rook) {
            return "r"; 
        } else if (n == PieceName::Knight) {
            return "n";
        } else if (n == PieceName::Pawn) {
            return "p";
        }
    }
    return "";
}


// Renders the board to the interface
void GraphicsDisplay::notify() {
	for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) { 
				Colour c = board->getBoard()[i][j]->getColour();
				PieceName p = board->getBoard()[i][j]->getType();
				char arr[6];
				if ((i+j) % 2) {
					strcpy(arr, (printPiece(p, c) + "b.bmp").c_str());
					w->drawImage(50*(j+1), 50*i, arr);
				} else {
					strcpy(arr, (printPiece(p, c) + "w.bmp").c_str());
					w->drawImage(50*(j+1), 50*i, arr);
				}
			} else {
				if ((i+j) % 2) {
					w->fillRectangle(50*(j+1), 50*i, 50, 50, 1);
				} else {
					w->fillRectangle(50*(j+1), 50*i, 50, 50, 0);
				}
			}
		}
	}
}

// Detach for deleting
GraphicsDisplay::~GraphicsDisplay() {
        board->detach(this);
}
