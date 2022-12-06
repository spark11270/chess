#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include "board.h"
#include "xwindow.h"

class GraphicsDisplay : public Observer {
	std::shared_ptr<Board> board;
	Xwindow *w;
	
	public:
		GraphicsDisplay(std::shared_ptr<Board> board);
		void notify() override;
		~GraphicsDisplay();
};	

#endif
