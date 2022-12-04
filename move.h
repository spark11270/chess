#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>
#include <string>
#include <memory>
#include "movetype.h"
#include "piecename.h"


class Piece;
class Move {
    public:
        std::shared_ptr<Piece> captured;
        std::shared_ptr<Piece> moving;
        std::pair<int, int> from;
        std::pair<int, int> to;
        MoveType tactic;

        // methods
        Move(std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic = MoveType::Normal);
        Move(std::shared_ptr<Piece> captured, std::shared_ptr<Piece> moving, std::pair<int, int>& from, std::pair<int, int>& to, MoveType tactic = MoveType::Normal);
        std::string getMoves();
};

#endif
