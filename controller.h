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
    int rounds;
    bool newRound;

public:
    Controller(Board* board);
    void initPlayer(const std::string& player, Colour colour);
    bool isValid(const std::pair<int, int> from, const std::pair<int, int> to);
    void initGame();
    void gameMoves();
    void playGame();
    void printScore();
};

#endif
