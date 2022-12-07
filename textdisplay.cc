#include "textdisplay.h"
#include "piecename.h"
#include "board.h"
#include "colour.h"
#include <iostream>
using namespace std;


// Changes enum piece class into characters representing each piece
// Im sure theres a better way to do this
char printPiece(PieceName n, Colour c) {
    if (c == Colour::White) {
        if (n == PieceName::King) {
            return 'K';
        } else if (n == PieceName::Queen) {
            return 'Q';
        } else if (n == PieceName::Bishop) {
            return 'B';
        } else if (n == PieceName::Rook) {
            return 'R'; 
        } else if (n == PieceName::Knight) {
            return 'N';
        } else if (n == PieceName::Pawn) {
            return 'P';
        }
        else {
            return ' ';
        }
    } else {
        if (n == PieceName::King) {
            return 'k';
        } else if (n == PieceName::Queen) {
            return 'q';
        } else if (n == PieceName::Bishop) {
            return 'b';
        } else if (n == PieceName::Rook) {
            return 'r'; 
        } else if (n == PieceName::Knight) {
            return 'n';
        } else if (n == PieceName::Pawn) {
            return 'p';
        }
        else {
            return ' ';
        }
    }
}

// Adds textdisplay observer to the subject
TextDisplay::TextDisplay(shared_ptr<Board> board) : board{board} {
	board->attach(this);
}

// Renders the board to the interface
void TextDisplay::notify() {
	for (int i = 0; i < 8; i++) {
        out << (8 - i) << ' ';
        for (int j = 0; j < 8; j++) {
            if (board->getBoard()[i][j] != nullptr) {
                out << printPiece(board->getBoard()[i][j]->getType(), board->getBoard()[i][j]->getColour());
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
    out << "  abcdefgh" << std::endl << std::endl;
}

// Detach for deleting
TextDisplay::~TextDisplay() {
	board->detach(this);
}          
