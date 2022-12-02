#include "board.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"

#include <iostream>

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
    } else {
        blackPieces.push_back(p);
    }
    int row = p->getCoords().first;
    int col = p->getCoords().second;
    theBoard[row][col] = p;
}

void Board::removePieceAt(const std::pair<int, int> &from) {
    shared_ptr<Piece> tmp = theBoard[from.first][from.second];
    if (theBoard[from.first][from.second] != nullptr) {
        theBoard[from.first][from.second] = nullptr;
        int pos = 0;
        if (tmp->getColour() == Colour::Black) {
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
    }
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
            cout << piece->getCoords().first << " " << piece->getCoords().second << endl;
            if (piece->getCoords().first == 7) return false;
        }
    }

    for (auto &piece : blackPieces) {
        if (piece->getType() == PieceName::Pawn) {
            cout << piece->getCoords().first << " " << piece->getCoords().second << endl;
            if (piece->getCoords().first == 0) return false;
        }
    }
}

void Board::init() {
    // white pieces
    theBoard[7][0] = make_shared<Rook>(Colour::White, 0, 0);
    theBoard[7][1] = make_shared<Knight>(Colour::White, 1, 0);
    theBoard[7][2] = make_shared<Bishop>(Colour::White, 2, 0);
    theBoard[7][3] = make_shared<King>(Colour::White, 3, 0);
    theBoard[7][4] = make_shared<Queen>(Colour::White, 4, 0);
    theBoard[7][5] = make_shared<Bishop>(Colour::White, 5, 0);
    theBoard[7][6] = make_shared<Knight>(Colour::White, 6, 0);
    theBoard[7][7] = make_shared<Rook>(Colour::White, 7, 0);

    // black pieces
    theBoard[0][0] = make_shared<Rook>(Colour::Black, 0, 0);
    theBoard[0][1] = make_shared<Knight>(Colour::Black, 1, 0);
    theBoard[0][2] = make_shared<Bishop>(Colour::Black, 2, 0);
    theBoard[0][3] = make_shared<King>(Colour::Black, 3, 0);
    theBoard[0][4] = make_shared<Queen>(Colour::Black, 4, 0);
    theBoard[0][5] = make_shared<Bishop>(Colour::Black, 5, 0);
    theBoard[0][6] = make_shared<Knight>(Colour::Black, 6, 0);
    theBoard[0][7] = make_shared<Rook>(Colour::Black, 7, 0);

    for (int i = 0 ; i < MAXCELL; ++i) {
        whitePieces.push_back(theBoard[i][7]);
        blackPieces.push_back(theBoard[i][0]);
    }

    // pawns
    for (int i = 0; i < MAXCELL; ++i) {
        theBoard[6][i] = make_shared<Pawn>(Colour::White, i, 1);
        theBoard[1][i] = make_shared<Pawn>(Colour::Black, i, 6);
        whitePieces.push_back(theBoard[i][6]);
        blackPieces.push_back(theBoard[i][1]);
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
    shared_ptr<Piece> p = theBoard[begin.first][begin.second];
    if (c == Colour::White) {
        // white's turn
        // isValidMove() is false;
        if (isWhiteTurn() && p->getColour() == c && p->isValidMove(begin, end)) {
            theBoard[end.first][end.second] = p;
            p->modifyCoords(end);
            theBoard[begin.first][begin.second] = nullptr;
        }
        else {
            throw runtime_error("invalid move");
        }
    }
    else {
        // black's turn
        if (!isWhiteTurn() && p->getColour() == c && p->isValidMove(begin, end)) {
            theBoard[end.first][end.second] = p;
            p->modifyCoords(end);
            theBoard[begin.first][begin.second] = nullptr;
        }
        else {
            throw runtime_error("invalid move");
        }
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

Board::~Board() {}