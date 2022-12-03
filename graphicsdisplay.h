#if 0

#include "observer.h"
#include "board.h"
#include "xwindow.h"

class GraphicsDisplay : public Observer {
	Board *board;
	Xwindow *w;
	
	public:
		GraphicsDisplay(Board* board);
		void notify() override;
		~GraphicsDisplay();
};	

#endif
