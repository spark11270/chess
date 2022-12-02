#include "computer.h"

#include <string>
#include <vector>

using namespace std;

Computer::Computer(Colour c, int lvl) : Player(c, 0), lvl{lvl} {}

vector<Move> Computer::getAIMoves() {}

Computer::~Computer() {}

char Computer::getType() {
    return 'c';
}
