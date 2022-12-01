#include "textdisplay.h"
#include "board.h"
#include "colour.h"


// Changes enum piece class into characters representing each piece
// Im sure theres a better way to do this
char numToPiece(int n, Colour c) {
    if (c == Colour::White) {
        if (n == 0) {
            return 'K';
        } else if (n == 1) {
            return 'Q';
        } else if (n == 2) {
            return 'B';
        } else if (n == 3) {
            return 'R'; 
        } else if (n == 4) {
            return 'K';
        } else if (n == 5) {
            return 'P';
        }
    } else {
        if (n == 0) {
            return 'k';
        } else if (n == 1) {
            return 'q';
        } else if (n == 2) {
            return 'b';
        } else if (n == 3) {
            return 'r'; 
        } else if (n == 4) {
            return 'k';
        } else if (n == 5) {
            return 'p';
        }
    }
}

// Adds textdisplay observer to the subject
TextDisplay::TextDisplay(Board* board) : board{board} {
	board->attach(this);
}

// Renders the board to the interface
void TextDisplay::notify() {
	for (int i = 0; i < 8; i++) {
        out << (8 - i) << ' ';
        for (int j = 0; j < 8; j++) {
            if (board->getPiece(i, j)) {
                out << numToPiece(board->getPiece(i, j)->getType(), board->getPiece(i, j)->getColour());
            } else {
                if ((i + j) % 2) {
                    out << '_';
                } else {
                    out << ' ';
                }
            }
        }
        out << std::endl;
    }
    out << std::endl;
    out << "  abcdefgh" << std::endl;
}

// Detach for deleting
TextDisplay::~TextDisplay() {
	board->detach(this);
}          