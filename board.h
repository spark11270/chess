#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "subject.h"
#include "colour.h"

#include <iostream>


class Move;
class Player;
class Piece;
class King;

class Board : public Subject {
    std::vector<std::vector<std::shared_ptr<Piece>>> theBoard{8, std::vector<std::shared_ptr<Piece>>{8}};
    std::vector<std::shared_ptr<Piece>> whitePieces{std::vector<std::shared_ptr<Piece>>{16}};
    std::vector<std::shared_ptr<Piece>> blackPieces{std::vector<std::shared_ptr<Piece>>{16}};
    Player *W; 
    Player *B;
    int rounds;

public:
    Board();
    void addPiece(std::pair<int, int> to, std::shared_ptr<Piece> p);
    void removePiece(std::pair<int, int> from);
    void init();
    void render();
    std::vector<std::vector<std::shared_ptr<Piece>>> getBoard();
    std::shared_ptr<Piece>getPiece(PieceName name);
    void move(int begin, int end);
    bool isCheck(std::pair<int, int> kingPos = std::make_pair(-1, -1));
    bool isCheckmate();
    void clear();
    ~Board();
};

#endif
