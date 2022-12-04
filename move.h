#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>
#include "movetype.h"

class Piece;
class Move {
    std::shared_ptr<Piece> captured;
    std::shared_ptr<Piece> moving;
    std::pair<int, int> from;
    std::pair<int, int> to;
    MoveType tactic;
    char undoProm; // character before promotion

    public:
        Move(std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic);
        Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic);
        void setCaptured(std::shared_ptr<Piece> captured);
};

#endif
