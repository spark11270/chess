#include "king.h"
#include "board.h"

using namespace std;

King::King(Board *b, Colour c, int row, int col) : Piece{b, c, PieceName::King, row, col} {}

bool King::isValidMove(std::pair<int, int> initial, std::pair<int, int> final) {

        Board *b = getTheBoard();

        if (outOfBounds(initial, final)) return false;

        // checks if king moves 2 squares
        if (b->canCastle(initial, final) != ' ') {
                // vertical
                if ((abs(initial.first - final.first) == 2) && (initial.second == final.second)) {
                        // set start and end row based on position
                        int start = final.first < initial.first ? final.first : initial.first;
                        int end = final.first < initial.first ? initial.first : final.first;
                        pair<int, int> tmp = make_pair(start, final.second);

                        // check every position the piece moves in for obstacles
                        for (int i = start + 1; i < end; ++i) {
                        tmp.first = i;
                        if (i != initial.first && getTheBoard()->hasObstacle(tmp)) return false;
                        }

                        return true;
                }
                // horizontal
                if ((abs(initial.second - final.second) == 2) && (initial.first = final.first)) {
                        // set start and end column based on position
                        int start = final.second < initial.second ? final.second : initial.second;
                        int end = final.second < initial.second ? initial.second : final.second;
                        pair<int, int> tmp = make_pair(final.first, start);

                        // check every position the piece moves in for obstacles
                        for (int i = start + 1; i < end; ++i) {
                        tmp.second = i;
                        if (i != initial.second && getTheBoard()->hasObstacle(tmp)) return false;  
                        }

                        return true;
                }
                return false;
        }

        // vertical
        if ((initial.first == final.first) && (abs(final.second - initial.second) == 1)) return true;

        // horizontal
        if ((initial.second == final.second) && (abs(final.first - initial.first) == 1)) return true; 
        
        // diagonal
        if ((abs(final.second - initial.second) == 1) && (abs(final.first - initial.first) == 1)) return true;

        return false;
}

vector<pair<int, int>> King::getPosMoves() {
    vector<pair<int, int>> moves;
    pair<int, int> init = getCoords();

    // vertical
    pair<int, int> pos = make_pair(init.first + 1, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first - 1, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // horizontal
    pos = make_pair(init.first, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // backward diagonal
    pos = make_pair(init.first + 1, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first - 1, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // forward diagonal
    pos = make_pair(init.first - 1, init.second - 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
    pos = make_pair(init.first + 1, init.second + 1);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }
  
    // move up 2 squares
    pos = make_pair(init.first + 2, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // move down 2 squares
    pos = make_pair(init.first - 2, init.second);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // move right 2 squares
    pos = make_pair(init.first, init.second + 2);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    // move left 2 squares
    pos = make_pair(init.first, init.second - 2);
    if (isValidMove(init, pos)) {
        moves.push_back(pos);
    }

    return moves;
}

PieceName King::getType() {return PieceName::King;}
