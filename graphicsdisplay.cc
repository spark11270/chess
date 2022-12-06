#include "graphicsdisplay.h"
#include "board.h"
#include "xwindow.h"
#include <string>
#include <cstring>

using namespace std;

// Adds graphicsdisplay observer to the subject
GraphicsDisplay::GraphicsDisplay(shared_ptr<Board>board) : board{board} {
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
	int from_x = 0;
	int from_y = 0;
	int to_x = 0;
        int to_y = 0;
	if (board->getTotalMoves().size()) {
		// Display capturing first before updating all boards
		from_x = board->getTotalMoves().back().from.first;
		from_y = board->getTotalMoves().back().from.second;
		to_x = board->getTotalMoves().back().to.first;
                to_y = board->getTotalMoves().back().to.second;
		int i = to_x;
		int j = to_y;
		Colour c = board->getBoard()[i][j]->getColour();
                PieceName p = board->getBoard()[i][j]->getType();
                                char arr[6];
				
				// Display Capture 	
                                if ((i+j) % 2) {
                                        strcpy(arr, (printPiece(p, c) + "b.bmp").c_str());
                                        w->drawImage(50*(j+1), 50*i, arr);
                                } else {
                                        strcpy(arr, (printPiece(p, c) + "w.bmp").c_str());
                                        w->drawImage(50*(j+1), 50*i, arr);
                                }
				// Fill the previous location of piece with rectangle
				if ((from_x+from_y) % 2) {
                                                w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 1);
                                        } else {
                                                w->fillRectangle(50*(from_y+1), 50*from_x, 50, 50, 0);
                                        }
	}
	
	// Update board
	for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
			// Update chess pieces
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
			// Update blank cells
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
