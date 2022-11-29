#include "move.h"

using namespace std;

Move::Move(std::vector<Cell> sequence, std::vector<Piece> caught) : sequence{sequence}, caught{caught} {}
