#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"
#include <string>
#include <memory>

class Board;
class LVL;

class Computer : public Player {
    private:
        std::shared_ptr<LVL> ai;

    public:
        Computer(Colour c, int lvl);
        ~Computer();

        char getType() override;
        std::shared_ptr<LVL> getAI();

        void move(std::shared_ptr<Board> board, std::pair<int, int> from, std::pair<int, int> to) override;
};

#endif
