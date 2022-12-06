#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {

public:
    // CONSTRUCTOR
    Queen(std::shared_ptr<Board> b, Colour c, int row, int col);

    // OVERRIDE
    virtual bool isValidMove(std::pair<int, int> initial, std::pair<int, int> final) override;
    virtual std::vector<std::pair<int, int>> getPosMoves() override;
    PieceName getType() override;

};

#endif
