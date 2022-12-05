#include "pawn.h"
#include "board.h"

using namespace std;

Pawn::Pawn(Colour c, int row, int col, Board *theBoard) : Piece{c, row, col, PieceName::Pawn, theBoard} {}

bool Pawn::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {
    if (final.first >= MAXCELL) return false; // check out of bounds
    if (final.second >= MAXCELL) return false; // check out of bounds
    
    if (final.first < 0) return false; // check out of bounds
    if (final.second < 0) return false; // check out of bounds
    
    if ((initial.first == final.first) && (initial.second == final.second)) return false; // you cannot stay in the same position

    // my own item?
    if (getTheBoard()->hasAlly(getColour(), final)) return false;
/*
    // can move 2 square forwards only if first move
    if (abs(initial.first - final.first) == abs(initial.second - final.second) && abs(initial.second - final.second) == 1) {
	    // move diagonally
        // if trying to capture
        if (getTheBoard()->hasObstacle(final)) return true;

        // if trying to enpassant

        if ((getTheBoard()->hasObstacle(final) == false) && (getTheBoard()->hasOpponent(getColour(), make_pair(initial.first, final.second))) && 
            (getTheBoard()->canEP(initial, final))) {
                return true;
            }
    }
        
  */
   
    // Get First move
    if (getIsFirstMove() == true) {
	    // For black pieces
	    if (getColour() == Colour::White) {
		    // Check for two steps
		    if ((initial.first - 2) == final.first) {
			    if (initial.second == final.second) {
				    // Cant go two steps with obstacle
				    if (getTheBoard()->hasObstacle(final)) {
					    return false;
				    } else {
					    return true;
				    }
			    } else {
				    return false;
			    }
		    }
	    // For white pieces
	    } else if (getColour() == Colour::Black) {
		    // Check for two steps
		    if ((initial.first + 2) == final.first) {
			    if (initial.second == final.second) {
                                    // Cant go two steps with obstacle
                                    if (getTheBoard()->hasObstacle(final)) {
                                            return false;
                                    } else {
                                            return true;
                                    }
                            } else {
                                    return false;
                            }
                    }
	    }
    }

    // Jae Test (Diagonal, Backwards)
    if (getColour() == Colour::White) {
	    // Going backwards => return false
	    if ((initial.first - 1) != final.first) {
		    return false;
	    // We dealt with pawn on the spot above
	    // So we look at invalid cases of pawn going forward
	    } else {
		    // Going one step forward
		    if (initial.second == final.second) {
			    // Return false if obstacle one step forward
			    if (getTheBoard()->hasObstacle(final)) {
				    return false;
			    } else {
				    return true;
			    }
		    // Cant go sideways
		    } else if ((initial.second == final.second + 1) || (initial.second == final.second - 1)) {
			    if (getTheBoard()->hasObstacle(final)) {
				    return true;
			    // Enpassant Check
			    } else if ((getTheBoard()->hasObstacle(final) == false) && 
						    (getTheBoard()->hasOpponent(getColour(), make_pair(initial.first, final.second))) &&
						    (getTheBoard()->canEP(initial, final))) {
				    return true;
			    // False Otherwise
			    } else {
				    return false;
			    }
		    } else {
			    return false;
		    }
	    }
	    return false;
    }
    if (getColour() == Colour::Black) {
	    // Going backwards => return false
	    if ((initial.first + 1) != final.first) {
                    return false;
            // We dealt with pawn on the spot above
            // So we look at invalid cases of pawn going forward
            } else {
                    // Going one step forward
                    if (initial.second == final.second) {
                            // Return false if obstacle one step forward
                            if (getTheBoard()->hasObstacle(final)) {
                                    return false;
                            } else {
				    return true;
			    }
		    // Cant go sideways
                    } else if ((initial.second == final.second + 1) || (initial.second == final.second - 1)) {
			    std::cout << getTheBoard()->hasObstacle(final)  << std::endl;
	       		    if (getTheBoard()->hasObstacle(final)) {
				    return true;
                            // Enpassant Check
                            } else if ((getTheBoard()->hasObstacle(final) == false) &&
                                                    (getTheBoard()->hasOpponent(getColour(), make_pair(initial.first, final.second))) &&
                                                    (getTheBoard()->canEP(initial, final))) {
				    return true;
                            // False Otherwise
                            } else {
                                    return false;
                            }
                    } else {
                            return false;
                    }
	    }
	    return false;
    }
    return false;
}
vector<pair<int, int>> Pawn::getPosMoves() {
    vector<pair<int, int>> moves;

    // black moves down
    if (getColour() == Colour::Black) {
        // single move forward
        pair<int, int> pos;
        pos.first = getCoords().first + 1;
        pos.second = getCoords().second;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getIsFirstMove() == true) { 
            pos.first = getCoords().first + 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
        pos.first = getCoords().first - 1;
        pos.second = getCoords().second - 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
        pos.second = getCoords().second + 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
    // white moves up
    } else {
        // single move forward
        pair<int, int> pos;
        pos.first = getCoords().first - 1;
        pos.second = getCoords().second;
        if (isValidMove(getCoords(), pos)) {
             moves.push_back(pos);
        }

        // can move 2 square forwards only if first move
        if (getIsFirstMove() == true) { 
            pos.first = getCoords().first - 2;
            pos.second = getCoords().second;
            if (isValidMove(getCoords(), pos)) {
                moves.push_back(pos);
            }
        }
        pos.first = getCoords().first + 1;
        pos.second = getCoords().second - 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
        pos.second = getCoords().second + 1;
        if (isValidMove(getCoords(), pos)) {
            moves.push_back(pos);
        }
    }
    return moves;
}

PieceName Pawn::getType() {return PieceName::Pawn;}
