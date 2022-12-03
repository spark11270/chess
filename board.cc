#include "board.h"
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
            cout << "PieceName::Bishop" << endl;
        }
        if (piece->getType() == PieceName::Pawn) {
            cout << "PieceName::Pawn" << endl;
        }
        if (piece->getType() == PieceName::King) {
            cout << "PieceName::King" << endl;
        }
        if (piece->getType() == PieceName::Queen) {
            cout << "PieceName::Queen" << endl;
        }
        if (piece->getType() == PieceName::Knight) {
            cout << "PieceName::Knight" << endl;
        }
        if (piece->getType() == PieceName::Rook) {
            cout << "PieceName::Rook" << endl;
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

void Board::removePieceAt(const std::pair<int, int> &from) {
    if (getPieceAt(from) == nullptr) return;

    int pos = 0;
    if (getPieceAt(from)->getColour() == Colour::Black) {
        for (auto &piece : blackPieces) {
            if (piece->getCoords().first == from.first && piece->getCoords().second == from.second) {
                blackPieces.erase(blackPieces.begin() + pos);
                break;
            }
            ++pos;
        }
    }
    else {
        for (auto &piece : whitePieces) {
            if (piece->getCoords().first == from.first && piece->getCoords().second == from.second) {
                whitePieces.erase(whitePieces.begin() + pos);
                break;
            }
            ++pos;
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
        ++kingCount.second;
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
    theBoard[7][0] = make_shared<Rook>(Colour::White, 7, 0);
    theBoard[7][1] = make_shared<Knight>(Colour::White, 7, 1);
    theBoard[7][2] = make_shared<Bishop>(Colour::White, 7, 2);
    theBoard[7][3] = make_shared<King>(Colour::White, 7, 3);
    theBoard[7][4] = make_shared<Queen>(Colour::White, 7, 4);
    theBoard[7][5] = make_shared<Bishop>(Colour::White, 7, 5);
    theBoard[7][6] = make_shared<Knight>(Colour::White, 7, 6);
    theBoard[7][7] = make_shared<Rook>(Colour::White, 7, 7);

    // black pieces
    theBoard[0][0] = make_shared<Rook>(Colour::Black, 0, 0);
    theBoard[0][1] = make_shared<Knight>(Colour::Black, 0, 1);
    theBoard[0][2] = make_shared<Bishop>(Colour::Black, 0, 2);
    theBoard[0][3] = make_shared<King>(Colour::Black, 0, 3);
    theBoard[0][4] = make_shared<Queen>(Colour::Black, 0, 4);
    theBoard[0][5] = make_shared<Bishop>(Colour::Black, 0, 5);
    theBoard[0][6] = make_shared<Knight>(Colour::Black, 0, 6);
    theBoard[0][7] = make_shared<Rook>(Colour::Black, 0, 7);

    for (int i = 0 ; i < MAXCELL; ++i) {
        whitePieces.push_back(theBoard[7][i]);
        blackPieces.push_back(theBoard[0][i]);
    }

    // pawns
    for (int i = 0; i < MAXCELL; ++i) {
        theBoard[6][i] = make_shared<Pawn>(Colour::White, 6, i);
        theBoard[1][i] = make_shared<Pawn>(Colour::Black, 1, i);
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

    // remove the piece
    removePieceAt(begin);

    // add the piece
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);

    // take the next turn
    nextTurn();
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