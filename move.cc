#include "move.h"

using namespace std;

Move::Move(shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) : 
    captured{nullptr}, moving{moving}, from{from}, to{to}, tactic{tactic} {
        undoProm = ' ';
    }

Move::Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic) :
    captured{captured}, moving{moving}, from{from}, to{to}, tactic{tactic} {
        undoProm = ' ';
    }

Move::Move(shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic, char undoProm) : 
    captured{nullptr}, moving{moving}, from{from}, to{to}, tactic{tactic}, undoProm{undoProm} {}

Move::Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic, char undoProm) :
    captured{captured}, moving{moving}, from{from}, to{to}, tactic{tactic}, undoProm{undoProm} {}

