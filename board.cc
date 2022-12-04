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
#include <utility>

using namespace std;

// -------------------------------- Helper ------------------------------
void printPiece(shared_ptr<Piece> &piece) {
    if (piece->getType() == PieceName::Bishop) {
        cout << "Bishop at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
    if (piece->getType() == PieceName::Pawn) {
        cout << "Pawn at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
    if (piece->getType() == PieceName::King) {
        cout << "King at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
    if (piece->getType() == PieceName::Queen) {
        cout << "Queen at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
    if (piece->getType() == PieceName::Knight) {
        cout << "Knight at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
    if (piece->getType() == PieceName::Rook) {
        cout << "Rook at " << piece->getCoords().first << ", " << piece->getCoords().second << endl;
    }
}

void printPieces(vector<shared_ptr<Piece>> pieces) {
    for (auto &piece: pieces) {
        printPiece(piece);
    }
}

Board::Board() {
    // construct theBoard
    for (int i = 0; i < MAXCELL; ++i) {
        for (int j = 0; j < MAXCELL; ++j) {
            theBoard[i][j] = nullptr;
        }
    }
}

void Board::addPiece(pair<int, int> coords, char piece) {
    shared_ptr<Piece> thePiece;
    switch(piece) {
        case 'K':
            thePiece = make_shared<King>(Colour::White, coords.first, coords.second, this);
            break;
        case 'Q':
            thePiece = make_shared<Queen>(Colour::White, coords.first, coords.second, this);
            break;
        case 'N':
            thePiece = make_shared<Knight>(Colour::White, coords.first, coords.second, this);
            break;
        case 'B':
            thePiece = make_shared<Bishop>(Colour::White, coords.first, coords.second, this);
            break;
        case 'R':
            thePiece = make_shared<Rook>(Colour::White, coords.first, coords.second, this);
            break;
        case 'P': 
            thePiece = make_shared<Pawn>(Colour::White, coords.first, coords.second, this);
            break;
        case 'k':
            thePiece = make_shared<King>(Colour::Black, coords.first, coords.second, this);
            break;
        case 'q':
            thePiece = make_shared<Queen>(Colour::Black, coords.first, coords.second, this);
            break;
        case 'n':
            thePiece = make_shared<Knight>(Colour::Black, coords.first, coords.second, this);
            break;
        case 'b':
            thePiece = make_shared<Bishop>(Colour::Black, coords.first, coords.second, this);
            break;
        case 'r':
            thePiece = make_shared<Rook>(Colour::Black, coords.first, coords.second, this);
            break;
        case 'p':
            thePiece = make_shared<Pawn>(Colour::Black, coords.first, coords.second, this);
            break;
    }
    if (thePiece->getColour() == Colour::White) {
        whitePieces.push_back(thePiece);
    }
    else {
        blackPieces.push_back(thePiece);
    }

    int row = thePiece->getCoords().first;
    int col = thePiece->getCoords().second;
    theBoard[row][col] = thePiece;
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
    return true;
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


std::shared_ptr<Piece> Board::getKing() {
    if (whosTurn == Colour::Black)   {
        for (auto &p : blackPieces) {
            if (p->getType() == PieceName::King) {
                return p;
            }
        }
    } else {
        for (auto &p : whitePieces) {
            if (p->getType() == PieceName::King) {
                return p;
            }
        }
    }
}

shared_ptr<Piece> Board::getPieceAt(const pair<int, int> &at) {
    return theBoard[at.first][at.second];
}

void Board::simulate(pair<int, int> &begin, pair<int, int> &end, MoveType type, char prom) {
    shared_ptr<Piece> p = getPieceAt(begin);

    // remove the piece
    theBoard[begin.first][begin.second] = nullptr;
    
    // add the piece
    if (getPieceAt(end) != nullptr) {
        removePieceAt(end); 
    }
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);

    if (type == MoveType::EnPassant) {
        removePieceAt(make_pair(end.first, end.second + 1));
        Move m{getPieceAt(make_pair(end.first, end.second + 1)), p, begin, end, MoveType::EnPassant};
        totalMoves.push_back(m);
    // promotion
    } else if (type == MoveType::Promotion) {
        removePieceAt(end);
        addPiece(end, prom);
        Move m{getPieceAt(end), p, begin, end, MoveType::Promotion};
        totalMoves.push_back(m);
    // capture
    } else if (type == MoveType::Capture) {
        Move m{getPieceAt(end), p, begin, end, MoveType::Capture};
        totalMoves.push_back(m);
    // normal
    } else {
        Move m{p, begin, end};
        totalMoves.push_back(m);
    }

    // check for if the move will lead to checkmate
    if (isCheck(getKing()->getCoords())) {
        undoMove(totalMoves.back());
        if (getWhosTurn() == Colour::White) {
            throw runtime_error("White King is in check");
        } else {
            throw runtime_error("Black King is in check");
        }
    }
}

Move Board::getLastMove(shared_ptr<Piece> p) {
    for (auto &m : totalMoves) {
        if (m.moving == p) {
            return m;
        }
    }
}

bool Board::canEP(pair<int, int> &begin, pair<int, int> &end) {
    shared_ptr<Piece> toCapture = getPieceAt(make_pair(begin.first, end.second));
    if (toCapture == nullptr) return false; // pawn must exists
    if (toCapture->getColour() == getPieceAt(begin)->getColour()) return false; // pawn must be opponent
    if (toCapture->getType() != PieceName::Pawn) return false;
    // check if the last move is pawn moving two squares
    Move m = totalMoves.back();
    cout << m.to.first << ", " << m.to.second << endl;
    if ((abs(m.to.first - m.from.first) == 2) && (m.to.first == begin.first) && (m.to.second == end.second)) {
        return true;
    }
    return false;
}

void Board::move(pair<int, int> &begin, pair<int, int> &end, MoveType type, char prom) {

     switch(type) {
        case MoveType::Normal :
            cout << "Normal" << endl;
            break;
        case MoveType::EnPassant :
            cout << "EnPassant" << endl;
            break;
        case MoveType::Capture :
            cout << "Capture" << endl;
            break;
        case MoveType::Castling :
            cout << "Castling" << endl;
            break;
        case MoveType::Promotion :
            cout << "Promotion" << endl;
            break;
    }


    shared_ptr<Piece> p = getPieceAt(begin);

    simulate(begin, end, type, prom);
    
    // remove the piece
    theBoard[begin.first][begin.second] = nullptr;
    
    // add the piece
    if (getPieceAt(end) != nullptr) {
        removePieceAt(end); 
    }
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);
    if (type == MoveType::EnPassant) {
        shared_ptr<Piece> removed = getPieceAt(begine.first, end.second); //opponent's pawn
        Move m{removed, p, begin, end, MoveType::EnPassant};
        removePieceAt(make_pair(begin.first, end.second));
        totalMoves.push_back(m);
    // promotion
    } else if (type == MoveType::Promotion) {
        removePieceAt(end);
        addPiece(end, prom);
        Move m{getPieceAt(end), p, begin, end, MoveType::Promotion};
        totalMoves.push_back(m);
    // capture
    } else if (type == MoveType::Capture) {
        Move m{getPieceAt(end), p, begin, end, MoveType::Capture};
        totalMoves.push_back(m);
    // normal
    } else {
        Move m{p, begin, end};
        totalMoves.push_back(m);
    }

    // for (auto &m : totalMoves) {
    //     cout << m.getMoves() << endl;
    // }

    nextTurn();
}

void Board::undoMove(const Move& m) {
    if (m.tactic == MoveType::Normal) {
        theBoard[m.from.first][m.from.second] = m.moving;
        theBoard[m.to.first][m.to.second] = nullptr;
    }
    if (m.tactic == MoveType::EnPassant) {
        theBoard[m.from.first][m.from.second] = m.moving;
        theBoard[m.to.first][m.to.second] = nullptr;
        shared_ptr<Piece> tmp = m.captured;
        if (tmp->getColour() == Colour::White) {
            whitePieces.push_back(tmp);
        }
        else {
            blackPieces.push_back(tmp);
        }
    }
    if (m.tactic == MoveType::Castling) {
        if (m.to.first == m.from.first) {
            // horizontal castling
            if ((m.to.second - m.to.second) < 0) {
                // rook moved to the left

                // move king to the right
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first, m.to.second + 1));
                theBoard[m.to.first][m.to.second + 1] = nullptr;
                theBoard[m.to.first][m.to.second - 1] = king;
            }
            else {
                // rook moved to the right

                // move king to the left
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first, m.to.second - 1));
                theBoard[m.to.first][m.to.second - 1] = nullptr;
                theBoard[m.to.first][m.to.second + 1] = king;
            }
        }
        else {
            if ((m.to.first - m.from.first) < 0) {
                // rook moved down
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first - 1, m.to.second));
                theBoard[m.to.first + 1][m.to.second] = nullptr;
                theBoard[m.to.first - 1][m.to.second] = king;
            }
            else {
                // rook moved up

                // move king up two squares
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first + 1, m.to.second));
                theBoard[m.to.first - 1][m.to.second] = nullptr;
                theBoard[m.to.first + 1][m.to.second] = king;
            }
        }

    // move rook to the right position
    theBoard[m.from.first][m.from.second] = m.moving;
    theBoard[m.to.first][m.to.second] = nullptr;
        
    }
    if (m.tactic == MoveType::Promotion) {
        if (m.captured == nullptr) {
            // no capturing
            removePieceAt(m.to);
            theBoard[m.to.first][m.to.first] = nullptr;
            if (m.moving->getColour() == Colour::White) {
                addPiece(m.from, 'P');
            }
            else {
                addPiece(m.from, 'p');
            }
        }
        else {
            removePieceAt(m.to);
            theBoard[m.to.first][m.to.first] = nullptr;
            if (m.moving->getColour() == Colour::White) {
                addPiece(m.from, 'P');
            }
            else {
                addPiece(m.from, 'p');
            }
            shared_ptr<Piece> tmp = m.captured;
            if (tmp->getColour() == Colour::White) {
                whitePieces.push_back(tmp);
            }
            else {
                blackPieces.push_back(tmp);
            }
        }
    }
    if (m.tactic == MoveType::Capture) {
        theBoard[m.from.first][m.from.second] = m.moving;
        theBoard[m.to.first][m.to.second] = nullptr;
        shared_ptr<Piece> tmp = m.captured;
        if (tmp->getColour() == Colour::White) {
            whitePieces.push_back(tmp);
        }
        else {
            blackPieces.push_back(tmp);
        }
    }
    totalMoves.pop_back();
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
    if (whosTurn == Colour::Black)   {
        for (auto &p : whitePieces) {
            PieceName name = p->getType();
            vector<pair<int, int>> moves = p->getPosMoves();
            if ((!moves.empty()) && (name != PieceName::King) && 
                (count(moves.begin(), moves.end(), kingPos) > 0)) {
                return true;
            }
        }
    } else {
        for (auto &p : blackPieces) {
            PieceName name = p->getType();
            vector<pair<int, int>> moves = p->getPosMoves();
            if ((!moves.empty()) && (name != PieceName::King) && 
                (count(moves.begin(), moves.end(), kingPos) > 0)) {
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
    if (isCheck(getKing()->getCoords())) {
        for (auto &cells : getKing()->getPosMoves()) {
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

void Board::nextTurn() {
    if (whosTurn == Colour::White) {
        whosTurn = Colour::Black;
    }
    else {
        whosTurn = Colour::White;
    }
}

Board::~Board() {}

vector<pair<shared_ptr<Piece>, pair<int, int>>> Board::getAllValidMoves(bool whiteTurn) {
    vector<pair<shared_ptr<Piece>, pair<int, int>>> validMovePairs;
    vector<shared_ptr<Piece>> &pieces = whiteTurn ? whitePieces : blackPieces;

    for (auto &piece : pieces) {
        vector<pair<int, int>> posMoves = piece->getPosMoves();
       
        for (auto &posMove : posMoves) {
            validMovePairs.emplace_back(piece, posMove);
        }
    }

    return validMovePairs;
}

bool Board::willLeadToCheck(std::pair<int, int> &to) {
    pair<int, int> kingPos = getKing()->getCoords();
    return kingPos.first == to.first && kingPos.second == to.second;
}

std::vector<Move> Board::getTotalMoves() {
	return totalMoves;
}
