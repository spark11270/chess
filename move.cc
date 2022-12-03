#include "move.h"

using namespace std;

Move::Move(int c_f, int r_f, int c_t, int r_t, shared_ptr<Piece> moving) : from{make_pair(c_f, r_f)}, to{make_pair(c_t, r_t)}, moving{moving} {}

void Move::setCaptured(shared_ptr<Piece> p) {
    captured = p;
}
