#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include "observer.h"
#include "board.h"

class TextDisplay : public Observer {
	Board *board;

	std::ostream &out = std::cout;
	
	public:
		TextDisplay(Board* board);
		void notify() override;
		~TextDisplay();
};	

#endif