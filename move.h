#ifndef _MOVE_H_
#define _MOVE_H_
#include <vector>

class Piece;

class Move {
    std::shared_ptr<Piece> captured;
    std::shared_ptr<Piece> moving;
    std::pair<int, int> from;
    std::pair<int, int> to;

public:
    Move(int c_f, int r_f, int c_t, int r_t, std::shared_ptr<Piece> moving);
    void setCaptured(std::shared_ptr<Piece> captured);
};

#endif
