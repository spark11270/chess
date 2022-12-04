#include "graphicsdisplay.h"
#include "board.h"
#include "xwindow.h"

// Adds graphicsdisplay observer to the subject
GraphicsDisplay::GraphicsDisplay(Board* board) : board{board} {
        w = new Xwindow(450, 450);
        w->drawBoard();
        board->attach(this);
}

// Renders the board to the interface
void GraphicsDisplay::notify() {
        for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                        if (board->getBoard()[i][j] != nullptr) {
				w->drawBigString(65+j*50, i*50+35, "K", 4);
			}
		}
	}
}

// Detach for deleting
GraphicsDisplay::~GraphicsDisplay() {
        board->detach(this);
}
