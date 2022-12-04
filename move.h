#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>
#include "movetype.h"

class Piece;
class Move {
    public:
        std::shared_ptr<Piece> captured;
        std::shared_ptr<Piece> moving;
        std::pair<int, int> from;
        std::pair<int, int> to;
        MoveType tactic;
        char undoProm; // character before promotion

        // methods
        Move(std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic);
        Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic);
        Move(std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic, char undoProm);
        Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic, char undoProm);
};

#endif
