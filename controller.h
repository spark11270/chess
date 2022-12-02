#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "colour.h"
#include "observer.h"
#include <memory>
#include <vector>

class Board;

class Controller {
    Board *board;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<Observer *> o;
    std::vector<Move> totalMoves;
    bool inGame;
    bool doneSetup;

public:
    Controller(Board* board);
    void initBoard();
    void initPlayers(const std::string, Colour colour);
    void playGame();
    void printScore();
};

#endif
