#include "board.h"

using namespace std;

Board::Board() : W{nullptr}, B{nullptr}, rounds{0} {
    // construct theBoard
    for (int i = 0; i < MAXCELL; i++) {
        for (int j = 0; j < MAXCELL; j++) {
            theBoard[i][j] = nullptr;
        }
    }
    // white/black pieces vector
    for (int i = 0; i < 16; i++) {
        whitePieces[i] = nullptr;
        blackPieces[i] = nullptr;
    }
}

void Board::init() {
    // white pieces
    theBoard[0][0] = make_shared<Rook>(Colour::White, 0, 0);
    theBoard[1][0] = make_shared<Knight>(Colour::White, 1, 0);
    theBoard[2][0] = make_shared<Bishop>(Colour::White, 2, 0);
    theBoard[3][0] = make_shared<King>(Colour::White, 3, 0);
    theBoard[4][0] = make_shared<Queen>(Colour::White, 4, 0);
    theBoard[5][0] = make_shared<Bishop>(Colour::White, 5, 0);
    theBoard[6][0] = make_shared<Knight>(Colour::White, 6, 0);
    theBoard[7][0] = make_shared<Rook>(Colour::White, 7, 0);

    // black pieces
    theBoard[0][7] = make_shared<Rook>(Colour::Black, 0, 0);
    theBoard[1][7] = make_shared<Knight>(Colour::Black, 1, 0);
    theBoard[2][7] = make_shared<Bishop>(Colour::Black, 2, 0);
    theBoard[3][7] = make_shared<King>(Colour::Black, 3, 0);
    theBoard[4][7] = make_shared<Queen>(Colour::Black, 4, 0);
    theBoard[5][7] = make_shared<Bishop>(Colour::Black, 5, 0);
    theBoard[6][7] = make_shared<Knight>(Colour::Black, 6, 0);
    theBoard[7][7] = make_shared<Rook>(Colour::Black, 7, 0);

    for (int i = 0 ; i < MAXCELL; ++i) {
        whitePieces.push_back(theBoard[i][0]);
        blackPieces.push_back(theBoard[i][7]);
    }

    // pawns
    for (int i = 0; i < MAXCELL; ++i) {
        theBoard[i][1] = make_shared<Pawn>(Colour::White, i, 1);
        theBoard[i][6] = make_shared<Pawn>(Colour::Black, i, 6);
        whitePieces.push_back(theBoard[i][1]);
        blackPieces.push_back(theBoard[i][6]);
    }
}

Piece *Board::getPiece(PieceName name) {
    if (turns % 2 == 0)   {
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

bool Board::isCheck(pair<int, int> kingPos) {
    if (kingPos.first == -1) {
        kingPos = getPiece(PieceName::king)->getCoords();
    }
    if (turns % 2 == 0)   {
        for (auto &p : whitePieces) {
            if (find(p->getPosMoves.begin(), p->getPosMoves.end(), kingPos) != p->getPosMoves.end()) {
                return true;
            }
        }
    } else {
        for (auto &p : blackPieces) {
           if (find(p->getPosMoves.begin(), p->getPosMoves.end(), kingPos) != p->getPosMoves.end()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isCheckmate() {
    if (isCheck()) {
        for (auto &cells : getKing()->getPosMoves) {
            if (isCheck(cells)) {
                return true;
            }
        }
    }
    return false;
}

void Board::clear() {
    // construct theBoard
    for (int i = 0; i < MAXCELL; i++) {
        for (int j = 0; j < MAXCELL; j++) {
            theBoard[i][j] = nullptr;
        }
    }
}

Board::~Board() {}