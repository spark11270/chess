#include <string>
#include <vector>
#include <utility>

#include "board.h"
#include "computer.h"
#include "lvl.h"
#include "lvl1.h"
#include "lvl2.h"
#include "lvl3.h"

using namespace std;

Computer::Computer(Colour c, int lvl) : Player(c, 0) {
    switch(lvl) {
        case 1:
            // random move
            ai = make_shared<LVL1>();
            break;
        case 2:
            // . prefers captures and checks
            ai = make_shared<LVL2>();
            break;
        case 3:
            // prefers avodiing capture and checks
            ai = make_shared<LVL3>();
            break;
    }
}


Computer::~Computer() {}

std::shared_ptr<LVL> Computer::getAI() {
    return ai;
}

char Computer::getType() {
    return 'c';
}

void Computer::move(Board *board, pair<int, int> from, pair<int, int> to) {
    pair<pair<int, int>, pair<int, int>> aiMove = ai.get()->getAIMove(board);
    board->move(aiMove.first, aiMove.second);
}