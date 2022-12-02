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
    std::vector<std::shared_ptr<Piece>> whitePieces;
    std::vector<std::shared_ptr<Piece>> blackPieces;
    Player *W; 
    Player *B;
    Colour whosTurn = Colour::White;

public:
    Board();
    bool isWhiteTurn();
    void setPlayerFirst(Colour colour);
    bool uniqueKing();
    bool validPawns();
    void init();
    void render();
    std::vector<std::vector<std::shared_ptr<Piece>>> getBoard();
    std::shared_ptr<Piece>getPiece(PieceName name, Colour colour);
    void addPiece(std::shared_ptr<Piece> p);
    void removePieceAt(const std::pair<int, int> &from);
    void move(const std::pair<int, int> &begin, const std::pair<int, int> &end, const Colour &c);
    bool isCheck(std::pair<int, int> kingPos = std::make_pair(-1, -1));
    bool isCheckmate();
    void clear();
    ~Board();
};

#endif
