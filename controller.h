#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include "colour.h"
#include "piecename.h"
#include "observer.h"
#include "player.h"

#include <string>
#include <memory>
#include <vector>
#include <sstream>

class Board;
class Move;

class Controller {
    Board *board;
    std::vector<std::unique_ptr<Player>> players;
    bool inGame;
    bool doneSetup;

public:
    Controller(Board* board);
    void initPlayer(const std::string& player, Colour colour);
    void initGame();
    void gameMoves();
    void playGame();
    void printScore();
};

#endif
