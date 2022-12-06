#include "human.h"
#include "board.h"
#include <string>

using namespace std;

Human::Human(Colour c) : Player(c, 0) {}

Human::~Human() {}

char Human::getType() {
    return 'h';
}

void Human::move(shared_ptr<Board> board, std::pair<int, int> from, std::pair<int, int> to) {
    board->move(from, to);
}