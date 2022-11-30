#include "computer.h"

#include <string>
#include <vector>

using namespace std;

Computer::Computer(std::string name, Colour c, int score, Level lvl) : Player(name, c, score), lvl{lvl} {}

vector<Move> Computer::getAIMoves() {}

Computer::~Computer() {}
