#include "board.h"
#include "move.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"

#include <iostream>
#include <algorithm>

using namespace std;

// -------------------------------- Helper ------------------------------
void printPieces(std::vector<std::shared_ptr<Piece>> pieces) {
    for (auto &piece: pieces) {
        if (piece->getType() == PieceName::Bishop) {
            cout << "Bishop" << endl;
        }
        if (piece->getType() == PieceName::Pawn) {
            cout << "Pawn" << endl;
        }
        if (piece->getType() == PieceName::King) {
            cout << "King" << endl;
        }
        if (piece->getType() == PieceName::Queen) {
            cout << "Queen" << endl;
        }
        if (piece->getType() == PieceName::Knight) {
            cout << "Knight" << endl;
        }
        if (piece->getType() == PieceName::Rook) {
            cout << "Rook" << endl;
        }
    }
}

Board::Board() : W{nullptr}, B{nullptr} {
    // construct theBoard
    for (int i = 0; i < MAXCELL; ++i) {
        for (int j = 0; j < MAXCELL; ++j) {
            theBoard[i][j] = nullptr;
        }
    }
}

void Board::addPiece(shared_ptr<Piece> p) {
    if (p->getColour() == Colour::White) {
        whitePieces.push_back(p);
    }
    else {
        blackPieces.push_back(p);
    }

    int row = p->getCoords().first;
    int col = p->getCoords().second;
    theBoard[row][col] = p;
}

void Board::removePieceAt(std::pair<int, int> from) {
    shared_ptr<Piece> tmp = theBoard[from.first][from.second];
    if (theBoard[from.first][from.second] != nullptr) {
        int pos = 0;
        if (tmp->getColour() == Colour::Black) {
            for (auto &piece : blackPieces) {
                if (piece->getCoords().first == from.first && piece->getCoords().second == from.second) {
                    blackPieces.erase(blackPieces.begin() + pos);
                    break;
                }
                ++pos;
            }
        } else {
            for (auto &piece : whitePieces) {
                if (piece->getCoords().first == from.first && piece->getCoords().second == from.second) {
                    whitePieces.erase(whitePieces.begin() + pos);
                    break;
                }
                ++pos;
            }
        }
    }
    
    theBoard[from.first][from.second] = nullptr;
}


bool Board::uniqueKing() {
    pair<int, int>  kingCount = make_pair(0, 0); // pair<white, black>
    for (auto &piece : whitePieces) {
        if (piece->getType() == PieceName::King) {
            ++kingCount.first;
        }
    }
    for (auto &piece : blackPieces) {
        if (piece->getType() == PieceName::King) {
            ++kingCount.second;
        }
    }

    if (kingCount.second == 1 && kingCount.first == 1) return true;
    return false;

}

bool Board::validPawns() {
    for (auto &piece : whitePieces) {
        if (piece->getType() == PieceName::Pawn) {
            if (piece->getCoords().first == 7) return false;
        }
    }

    for (auto &piece : blackPieces) {
        if (piece->getType() == PieceName::Pawn) {
            if (piece->getCoords().first == 0) return false;
        }
    }
}

void Board::init() {
    // white pieces
    theBoard[7][0] = make_shared<Rook>(Colour::White, 7, 0, this);
    theBoard[7][1] = make_shared<Knight>(Colour::White, 7, 1, this);
    theBoard[7][2] = make_shared<Bishop>(Colour::White, 7, 2, this);
    theBoard[7][3] = make_shared<King>(Colour::White, 7, 3, this);
    theBoard[7][4] = make_shared<Queen>(Colour::White, 7, 4, this);
    theBoard[7][5] = make_shared<Bishop>(Colour::White, 7, 5, this);
    theBoard[7][6] = make_shared<Knight>(Colour::White, 7, 6, this);
    theBoard[7][7] = make_shared<Rook>(Colour::White, 7, 7, this);

    // black pieces
    theBoard[0][0] = make_shared<Rook>(Colour::Black, 0, 0, this);
    theBoard[0][1] = make_shared<Knight>(Colour::Black, 0, 1, this);
    theBoard[0][2] = make_shared<Bishop>(Colour::Black, 0, 2, this);
    theBoard[0][3] = make_shared<King>(Colour::Black, 0, 3, this);
    theBoard[0][4] = make_shared<Queen>(Colour::Black, 0, 4, this);
    theBoard[0][5] = make_shared<Bishop>(Colour::Black, 0, 5, this);
    theBoard[0][6] = make_shared<Knight>(Colour::Black, 0, 6, this);
    theBoard[0][7] = make_shared<Rook>(Colour::Black, 0, 7, this);

    for (int i = 0 ; i < MAXCELL; ++i) {
        whitePieces.push_back(theBoard[7][i]);
        blackPieces.push_back(theBoard[0][i]);
    }

    // pawns
    for (int i = 0; i < MAXCELL; ++i) {
        theBoard[6][i] = make_shared<Pawn>(Colour::White, 6, i, this);
        theBoard[1][i] = make_shared<Pawn>(Colour::Black, 1, i, this);
        whitePieces.push_back(theBoard[6][i]);
        blackPieces.push_back(theBoard[1][i]);
    }
}


void Board::render() {
    notifyObservers();
}


vector<vector<shared_ptr<Piece>>> Board::getBoard() {
    return theBoard;
}


std::shared_ptr<Piece> Board::getPiece(PieceName name, Colour colour) {
    if (colour == Colour::Black)   {
        for (auto &p : blackPieces) {
            if (p->getType() == name) {
                return p;
            }
        }
    } else {
        for (auto &p : whitePieces) {
            if (p->getType() == name) {
                return p;
            }
        }
    }
}

void Board::move(pair<int, int> &begin, pair<int, int> &end, Colour c) {
    bool validTurn = isValidTurn(begin);

    if (!validTurn) {
        throw runtime_error("Wrong player's turn to move");
    }

    shared_ptr<Piece> p = getPieceAt(begin);
    bool validMove = p->isValidMove(begin, end);

    if (!validMove) {
        throw runtime_error("Illegal move");
    }
    
    // check for if the move will lead to checkmate
    if (isCheck()) {
        if (getWhosTurn() == Colour::White) {
            throw runtime_error("White King is in check");
        } else {
            throw runtime_error("Black King is in check");
        }
    }

    // capture
    if (hasOpponent(p->getColour(), getPieceAt(end)->getCoords())) {
        Move m{begin.first, begin.second, end.first, end.second, p};
        m.setCaptured(getPieceAt(end));
        totalMoves.push_back(m);
    }
    
    // remove the piece
    theBoard[begin.first][begin.second] = nullptr;
    
    // add the piece
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);

    // take the next turn
    nextTurn();
}

void Board::promotion(std::pair<int, int> &begin, std::pair<int, int> &end, Colour c, char prom) {
    move(begin, end, c);
    removePieceAt(end);
    shared_ptr<Piece> p = getPieceAt(begin);
    if ((end.first == 0 && p->getColour() == Colour::White)) {
        switch(prom) {
            case 'R':
                theBoard[end.first][end.second] = make_shared<Rook>(Colour::White, end.first, end.second, this);
                break;
            case 'B':
                theBoard[end.first][end.second] = make_shared<Bishop>(Colour::White, end.first, end.second, this);
                break;
            case 'N':
                theBoard[end.first][end.second] = make_shared<Knight>(Colour::White, end.first, end.second, this);
                break;
            case 'Q':
                theBoard[end.first][end.second] = make_shared<Queen>(Colour::White, end.first, end.second, this);
                break;
        }
    } else if (end.first == 7 && p->getColour() == Colour::Black) {
        switch(prom) {
            case 'r':
                theBoard[end.first][end.second] = make_shared<Rook>(Colour::Black, end.first, end.second, this);
                break;
            case 'b':
                theBoard[end.first][end.second] = make_shared<Bishop>(Colour::Black, end.first, end.second, this);
                break;
            case 'n':
                theBoard[end.first][end.second] = make_shared<Knight>(Colour::Black, end.first, end.second, this);
                break;
            case 'q':
                theBoard[end.first][end.second] = make_shared<Queen>(Colour::Black, end.first, end.second, this);

                break;
        }
    }
    if (whosTurn == Colour::White) {
        blackPieces.push_back(theBoard[end.first][end.second]);
    }
    else {
        whitePieces.push_back(theBoard[end.first][end.second]);
    }
}

bool Board::isWhiteTurn() {
    if (whosTurn == Colour::White) return true;
    return false;
}

void Board::setPlayerFirst(Colour colour) {
    if (colour == Colour::Black) {
        whosTurn = Colour::Black;
    }
    else if (colour == Colour::White) {
        whosTurn = Colour::White;
    }
    else {
        throw runtime_error("Please enter a valid colour");
    }
}

bool Board::isCheck(pair<int, int> kingPos) {
    if (kingPos.first == -1) {
        kingPos = getPiece(PieceName::King, whosTurn)->getCoords();
    }
    if (whosTurn == Colour::Black)   {
        for (auto &p : whitePieces) {
            if (find(p->getPosMoves().begin(), p->getPosMoves().end(), kingPos) != p->getPosMoves().end()) {
                return true;
            }
        }
    } else {
        for (auto &p : blackPieces) {
           if (find(p->getPosMoves().begin(), p->getPosMoves().end(), kingPos) != p->getPosMoves().end()) {
                return true;
            }
        }
    }
    return false;
}

Colour Board::getWhosTurn() {
    return whosTurn;
}

bool Board::isCheckmate() {
    if (isCheck()) {
        for (auto &cells : getPiece(PieceName::King, whosTurn)->getPosMoves()) {
            if (isCheck(cells)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::hasAlly(Colour c, const pair<int, int> pos) {
    shared_ptr<Piece> tmp = theBoard[pos.first][pos.second];
    if (c == Colour::Black) {
        if (tmp != nullptr && tmp->getColour() == Colour::Black) return true;
        return false;
    }
    else {
        if (tmp != nullptr && tmp->getColour() == Colour::White) return true;
        return false;
    }
}

bool Board::hasOpponent(Colour c, const pair<int, int> pos) {
    shared_ptr<Piece> tmp = theBoard[pos.first][pos.second];
    if (c == Colour::White) {
        if (tmp != nullptr && tmp->getColour() == Colour::Black) return true;
        return false;
    }
    else {
        if (tmp != nullptr && tmp->getColour() == Colour::White) return true;
        return false;
    }
}

bool Board::hasObstacle(pair<int, int> pos) {
    shared_ptr<Piece> tmp = theBoard[pos.first][pos.second];
    return tmp != nullptr;
}

void Board::clear() {
    // turn = white by default
    whosTurn = Colour::White;

    // clear out the pieces of the previous game;
    whitePieces.clear();
    blackPieces.clear();
    // construct theBoard
    for (int i = 0; i < MAXCELL; i++) {
        for (int j = 0; j < MAXCELL; j++) {
            theBoard[i][j] = nullptr;
        }
    }
}

shared_ptr<Piece> Board::getPieceAt(const pair<int, int> &at) {
    return theBoard[at.first][at.second];
}

bool Board::isValidTurn(const pair<int, int> &from) {
    shared_ptr<Piece> piece = getPieceAt(from);
    if (piece == nullptr) return false;
    if (piece->getColour() != whosTurn) return false;
    return true;
}

void Board::nextTurn() {
    if (whosTurn == Colour::White) {
        whosTurn = Colour::Black;
    }
    else {
        whosTurn = Colour::White;
    }
}

Board::~Board() {}