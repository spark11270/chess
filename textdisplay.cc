#include "textdisplay.h"
#include "board.h"
#include "colour.h"


// Changes enum piece class into characters representing each piece
// Im sure theres a better way to do this
char printPiece(PieceName n, Colour c) {
    if (c == Colour::White) {
        if (n == PieceName::king) {
            return 'K';
        } else if (PieceName::queen) {
            return 'Q';
        } else if (PieceName::bishop) {
            return 'B';
        } else if (PieceName::rook) {
            return 'R'; 
        } else if (PieceName::knight) {
            return 'N';
        } else if (PieceName::pawn) {
            return 'P';
        }
    } else {
        if (n == PieceName::king) {
            return 'k';
        } else if (PieceName::queen) {
            return 'q';
        } else if (PieceName::bishop) {
            return 'b';
        } else if (PieceName::rook) {
            return 'r'; 
        } else if (PieceName::knight) {
            return 'n';
        } else if (PieceName::pawn) {
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
            if (board->getBoard()[i][j] != nullptr) {
                out << board->getBoard()[i][j]->getType(), board->getBoard()[i][j]->getColour();
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