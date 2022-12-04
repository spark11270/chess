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

Board::Board() : W{nullptr}, B{nullptr} {
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

void Board::move(pair<int, int> &begin, pair<int, int> &end) {
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
    if (isCheck(getKing()->getCoords())) {
        if (getWhosTurn() == Colour::White) {
            throw runtime_error("White King is in check");
        } else {
            throw runtime_error("Black King is in check");
        }
    }

    // capture
    // if (hasOpponent(p->getColour(), getPieceAt(end)->getCoords())) {
    //     Move m{begin.first, begin.second, end.first, end.second, p};
    //     m.setCaptured(getPieceAt(end));
    //     totalMoves.push_back(m);
    // }
    
    // remove the piece
    theBoard[begin.first][begin.second] = nullptr;
    
    // add the piece
    if (getPieceAt(end) != nullptr) {
        removePieceAt(end); 
    }
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);

    // take the next turn
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
            addPiece(m.from, m.undoProm);
        }
        else {
            removePieceAt(m.to);
            theBoard[m.to.first][m.to.first] = nullptr;
            addPiece(m.from, m.undoProm);
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

void Board::promotion(std::pair<int, int> &begin, std::pair<int, int> &end, char prom) {
    move(begin, end);
    removePieceAt(end);
    addPiece(end, prom);
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
    // debugging
    // if (whosTurn == Colour::White) {
    //     cout << "white king pos: ";
    // } else {
    //     cout << "black king pos: ";
    // }
    // cout << kingPos.first <<", " << kingPos.second << endl;

    if (whosTurn == Colour::Black)   {
        for (auto &p : whitePieces) {
            cout << "i ran" << endl;
            PieceName name = p->getType();
            // switch(name) {
            //     case PieceName::Bishop :
            //         cout << "Bishop moves: " << endl;
            //         break;
            //     case PieceName::Queen :
            //         cout << "Queen moves: " << endl;
            //         break;
            //     case PieceName::Pawn :
            //         cout << "Pawn moves: " << endl;
            //         break;
            //     case PieceName::Rook :
            //         cout << "Rook moves: " << endl;
            //         break;
            //     case PieceName::Knight :
            //         cout << "Knight moves: " << endl;
            //         break;
            //     case PieceName::King :
            //         cout << "King moves: " << endl;
            //         break;
            // }
            // for (auto &m : p->getPosMoves()) {
            //     cout << m.first << ", " << m.second << endl;
            // }
            vector<pair<int, int>> moves = p->getPosMoves();
            if ((!moves.empty()) && (name != PieceName::King) && 
                (count(moves.begin(), moves.end(), kingPos) > 0)) {
                return true;
            }
        }
    } else {
        for (auto &p : blackPieces) {
            PieceName name = p->getType();
            // switch(name) {
            //     case PieceName::Bishop :
            //         cout << "Bishop moves: " << endl;
            //         break;
            //     case PieceName::Queen :
            //         cout << "Queen moves: " << endl;
            //         break;
            //     case PieceName::Pawn :
            //         cout << "Pawn moves: " << endl;
            //         break;
            //     case PieceName::Rook :
            //         cout << "Rook moves: " << endl;
            //         break;
            //     case PieceName::Knight :
            //         cout << "Knight moves: " << endl;
            //         break;
            //     case PieceName::King :
            //         cout << "King moves: " << endl;
            //         break;
            // }
            // for (auto &m : p->getPosMoves()) {
            //     cout << m.first << ", " << m.second << endl;
            // }
            vector<pair<int, int>> moves = p->getPosMoves();
            if ((!moves.empty()) && (name != PieceName::King) && 
                (count(moves.begin(), moves.end(), kingPos) > 0)) {
                // switch(name) {
                //     case PieceName::Bishop :
                //         cout << "Bishop moves: " << endl;
                //         break;
                //     case PieceName::Queen :
                //         cout << "Queen moves: " << endl;
                //         break;
                //     case PieceName::Pawn :
                //         cout << "Pawn moves: " << endl;
                //         break;
                //     case PieceName::Rook :
                //         cout << "Rook moves: " << endl;
                //         break;
                //     case PieceName::Knight :
                //         cout << "Knight moves: " << endl;
                //         break;
                //     case PieceName::King :
                //         cout << "King moves: " << endl;
                //         break;
                // }
                // for (auto &m : p->getPosMoves()) {
                //     cout << m.first << ", " << m.second << endl;
                // }
                // cout << "ischeck here" << endl;
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


