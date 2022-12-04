#include "move.h"

using namespace std;

Move::Move(shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) : 
    captured{nullptr}, moving{moving}, from{from}, to{to}, tactic{tactic} {}

Move::Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) :
    captured{captured}, moving{moving}, from{from}, to{to}, tactic{tactic} {}


void Move::setCaptured(shared_ptr<Piece> p) {
    captured = p;
}
