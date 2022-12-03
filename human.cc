#include "human.h"
#include "board.h"
#include <string>

using namespace std;

Human::Human(Colour c) : Player(c, 0) {}

Human::~Human() {}

void Human::move(Board *board, std::pair<int, int> from, std::pair<int, int> to) {
    board->move(from, to);
}