#include "move.h"

using namespace std;

Move::Move(int c_f, int r_f, int c_f, int r_f, Piece* captured, Piece* moving) :
    c_f{c_f}, r_f{r_f}, c_t{c_t}, r_t{r_t}, captured{captured}, moving{moving} {}
