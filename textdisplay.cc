#include "textdisplay.h"
#include "board.h"

TextDisplay::TextDisplay(Board* board) : board{board} {
	board->attach(this);
}

void TextDisplay::notify() {
	for (int i = 0; i < 8; i++) {
        out << (8 - i) << ' ';
        for (int j = 0; j < 8; j++) {
            out << '0'; //board->getCell(i, j).getPiece();
        }
        out << std::endl;
    }
    out << std::endl;
    out << "  abcdefgh" << std::endl;
}

TextDisplay::~TextDisplay() {
	board->detach(this);
}          