#include "graphicsdisplay.h"
#include "board.h"

// Adds graphicsdisplay observer to the subject
GraphicsDisplay::GraphicsDisplay(Board* board) : board{board} {
	board->attach(this);
}

// Renders the board to the interface
void GraphicsDisplay::notify() {
	w->drawBoard();
}

// Detach for deleting
GraphicsDisplay::~GraphicsDisplay() {
	board->detach(this);
}          
