#include "human.h"

using namespace std;

Human::Human(Colour c) : Player(c, 0) {}

Human::~Human() {}

char Human::getType() {
    return 'h';
}
