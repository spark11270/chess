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
    std::vector<Move> totalMoves;
    Player *W; 
    Player *B;
    Colour whosTurn = Colour::White;

public:
    Board();
    // true if white's turn
    bool isWhiteTurn();
    // set the given player to play first
    void setPlayerFirst(Colour colour);
    // checks if there is a unique king for each player
    bool uniqueKing();
    // checks if pawns are not at the first and the last rown
    bool validPawns();
    // initialize the board with nullptr
    void init();
    void render();
    // returns the cureent board
    std::vector<std::vector<std::shared_ptr<Piece>>> getBoard();
    // returns the position of the King of the given colour
    std::shared_ptr<Piece> getKing();
    void addPiece(std::pair<int, int> pos, char c);
    void removePieceAt(std::pair<int, int> from);
    void move(std::pair<int, int> &begin, std::pair<int, int> &end);
    void promotion(std::pair<int, int> &begin, std::pair<int, int> &end, char prom);

    bool isCheck(std::pair<int, int> kingPos);
    bool isCheckmate();
    // returns true if has ally at the given position
    bool hasAlly(Colour c, const std::pair<int, int> pos);
    // returns true if has opponent at the given position
    bool hasOpponent(Colour c, const std::pair<int, int> pos);
    // returns true if has either opponent/ally at the given position
    bool hasObstacle(const std::pair<int, int> pos);
    // clear out all the pieces at the board
    void clear();
    // returns White if white's turn and Black otherwise
    Colour getWhosTurn();

    std::vector<std::pair<std::shared_ptr<Piece>, std::pair<int, int>>> getAllValidMoves(bool whiteTurn);
    bool willLeadToCheck(std::pair<int, int> &to);
    // returns the piece of the given position
    std::shared_ptr<Piece> getPieceAt(const std::pair<int, int> &at);
    // returns true if moving from current location is valid
    bool isValidTurn(const std::pair<int, int> &from);
    // set whosturn to the next player
    void nextTurn();
    // logic for computer
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getAllValidMoves(bool whiteTurn);
    ~Board();
};

#endif
