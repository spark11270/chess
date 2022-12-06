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

const char UP = 'u';
const char DOWN = 'd';
const char RIGHT = 'r';
const char LEFT = 'l';

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

void printMoves(vector<pair<shared_ptr<Piece>, pair<int, int>>> &moves) {
    for (auto &move : moves) {
        printPiece(move.first);
        cout << move.second.first << ", " << move.second.second << endl;
    }
}

void printPieces(vector<shared_ptr<Piece>> pieces) {
    for (auto &piece: pieces) {
        printPiece(piece);
    }
}

shared_ptr<Piece> Board::getRook(pair<int,int> kingPos, char kingDir, Colour c) {
    if (c == Colour::Black) {
        for (auto &piece : blackPieces) {
            if (piece->getType() == PieceName::Rook) {
                if (kingDir == UP) {
                    if (piece->getCoords().first < kingPos.first && piece->getCoords().second == kingPos.second) {
                        return piece;
                    }
                } if (kingDir == DOWN) {
                    if (piece->getCoords().first > kingPos.first && piece->getCoords().second == kingPos.second) {
                        return piece;
                    }
                } if (kingDir == RIGHT) {
                    if (piece->getCoords().second > kingPos.second && piece->getCoords().first == kingPos.first) {
                        return piece;
                    }
                }
                if (kingDir == LEFT) {
                    if (piece->getCoords().second < kingPos.second && piece->getCoords().first == kingPos.first) {
                        return piece;
                    }

                }
            }
        }
    } else {
        for (auto &piece : whitePieces) {
            if (piece->getType() == PieceName::Rook) {
                if (kingDir == UP) {
                    if (piece->getCoords().first < kingPos.first && piece->getCoords().second == kingPos.second) {
                        return piece;
                    }
                } if (kingDir == DOWN) {
                    if (piece->getCoords().first > kingPos.first && piece->getCoords().second == kingPos.second) {
                        return piece;
                    }
                } if (kingDir == RIGHT) {
                    if (piece->getCoords().second > kingPos.second && piece->getCoords().first == kingPos.first) {
                        return piece;
                    }
                }
                if (kingDir == LEFT) {
                    if (piece->getCoords().second < kingPos.second && piece->getCoords().first == kingPos.first) {
                        return piece;
                    }

                }
            }
        }
    }
    return nullptr;
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
            thePiece = make_shared<King>(this, Colour::White, coords.first, coords.second);
            break;
        case 'Q':
            thePiece = make_shared<Queen>(this, Colour::White, coords.first, coords.second);
            break;
        case 'N':
            thePiece = make_shared<Knight>(this, Colour::White, coords.first, coords.second);
            break;
        case 'B':
            thePiece = make_shared<Bishop>(this, Colour::White, coords.first, coords.second);
            break;
        case 'R':
            thePiece = make_shared<Rook>(this, Colour::White, coords.first, coords.second);
            break;
        case 'P': 
            thePiece = make_shared<Pawn>(this, Colour::White, coords.first, coords.second);
            break;
        case 'k':
            thePiece = make_shared<King>(this, Colour::Black, coords.first, coords.second);
            break;
        case 'q':
            thePiece = make_shared<Queen>(this, Colour::Black, coords.first, coords.second);
            break;
        case 'n':
            thePiece = make_shared<Knight>(this, Colour::Black, coords.first, coords.second);
            break;
        case 'b':
            thePiece = make_shared<Bishop>(this, Colour::Black, coords.first, coords.second);
            break;
        case 'r':
            thePiece = make_shared<Rook>(this, Colour::Black, coords.first, coords.second);
            break;
        case 'p':
            thePiece = make_shared<Pawn>(this, Colour::Black, coords.first, coords.second);
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
    theBoard[7][0] = make_shared<Rook>(this, Colour::White, 7, 0);
    theBoard[7][1] = make_shared<Knight>(this, Colour::White, 7, 1);
    theBoard[7][2] = make_shared<Bishop>(this, Colour::White, 7, 2);
    theBoard[7][3] = make_shared<Queen>(this, Colour::White, 7, 3);
    theBoard[7][4] = make_shared<King>(this, Colour::White, 7, 4);
    theBoard[7][5] = make_shared<Bishop>(this, Colour::White, 7, 5);
    theBoard[7][6] = make_shared<Knight>(this, Colour::White, 7, 6);
    theBoard[7][7] = make_shared<Rook>(this, Colour::White, 7, 7);

    // black pieces
    theBoard[0][0] = make_shared<Rook>(this, Colour::Black, 0, 0);
    theBoard[0][1] = make_shared<Knight>(this, Colour::Black, 0, 1);
    theBoard[0][2] = make_shared<Bishop>(this, Colour::Black, 0, 2);
    theBoard[0][3] = make_shared<Queen>(this, Colour::Black, 0, 3);
    theBoard[0][4] = make_shared<King>(this, Colour::Black, 0, 4);
    theBoard[0][5] = make_shared<Bishop>(this, Colour::Black, 0, 5);
    theBoard[0][6] = make_shared<Knight>(this, Colour::Black, 0, 6);
    theBoard[0][7] = make_shared<Rook>(this, Colour::Black, 0, 7);

    for (int i = 0 ; i < MAXCELL; ++i) {
        whitePieces.push_back(theBoard[7][i]);
        blackPieces.push_back(theBoard[0][i]);
    }

    // pawns
    for (int i = 0; i < MAXCELL; ++i) {
        theBoard[6][i] = make_shared<Pawn>(this, Colour::White, 6, i);
        theBoard[1][i] = make_shared<Pawn>(this, Colour::Black, 1, i);
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
    return nullptr;
}

shared_ptr<Piece> Board::getPieceAt(const pair<int, int> &at) {
    return theBoard[at.first][at.second];
}

void Board::simulate(pair<int, int> &begin, pair<int, int> &end, MoveType type, char prom, char dir) {
    shared_ptr<Piece> p = getPieceAt(begin);
    shared_ptr<Piece> captured = getPieceAt(end);

    // remove the piece
    theBoard[begin.first][begin.second] = nullptr;
    // add the piece
    if (getPieceAt(end) != nullptr) {
        removePieceAt(end); 
    }
    theBoard[end.first][end.second] = p;

    // modify the piece coordinate
    p->modifyCoords(end);
    if (type == MoveType::Castling) {
        shared_ptr<Piece> rook = getRook(getKing()->getCoords(), dir, whosTurn);

        pair<int, int> rookPos;
        theBoard[rook->getCoords().first][rook->getCoords().second] = nullptr;
        switch(dir) {
            // move rook one left of king
            case RIGHT:
                rookPos = make_pair(end.first, end.second - 1);
                break;
            // move rook one right of king
            case LEFT:
                rookPos = make_pair(end.first, end.second + 1);
                break;
            // move rook one down of king
            case UP:
                rookPos = make_pair(end.first + 1, end.second);
                break;
            // move rook one right of king
            case DOWN:
                rookPos = make_pair(end.first - 1, end.second);
                break;
        }
        theBoard[rookPos.first][rookPos.second] = rook;
        rook->modifyCoords(rookPos);
        Move m{p, begin, end, MoveType::Castling};
        totalMoves.push_back(m);
    } else if (type == MoveType::EnPassant) {
        shared_ptr<Piece> removed = getPieceAt(make_pair(begin.first, end.second)); //opponent's pawn
        Move m{removed, p, begin, end, MoveType::EnPassant};
        removePieceAt(make_pair(begin.first, end.second));
        totalMoves.push_back(m);
    } else if (type == MoveType::Promotion) {
        removePieceAt(end);
        addPiece(end, prom);
        // promotion + capture
        if (captured != nullptr) {
            Move m{captured, p, begin, end, MoveType::Promotion};
        }
        // normal promotion
        else {
            Move m{p, begin, end, MoveType::Promotion};
        }
    } else if (type == MoveType::Capture) {
        Move m{captured, p, begin, end, MoveType::Capture};
        totalMoves.push_back(m);
    } else {
        Move m{p, begin, end};
        totalMoves.push_back(m);
    }
}

Move Board::getLastMove() {
    return totalMoves.back();
}

bool Board::canEP(pair<int, int> &begin, pair<int, int> &end) {
    shared_ptr<Piece> toCapture = getPieceAt(make_pair(begin.first, end.second));
    if (toCapture == nullptr) return false; // pawn must exist
    if (toCapture->getColour() == getPieceAt(begin)->getColour()) return false; // pawn must be opponent
    if (toCapture->getType() != PieceName::Pawn) return false;
    // check if the last move is pawn moving two squares
    Move m = totalMoves.back();
    if ((abs(m.to.first - m.from.first) == 2) && (m.to.first == begin.first) && (m.to.second == end.second)) {
        return true;
    }
    return false;
}

// already a valid king move
char Board::canCastle(pair<int, int> begin, pair<int, int> end) {
    shared_ptr<Piece> king = getPieceAt(begin);
    shared_ptr<Piece> rook;
    char direction;
    char garbage = ' ';

    pair<int, int> dir;
     // same row
    if (begin.first == end.first && abs(begin.second - end.second) == 2) {
       dir.first = 0;
       if (begin.second > end.second) {
        // moves left
        dir.second = -1;
        rook = getRook(king->getCoords(), LEFT, whosTurn);
        direction = LEFT;
       }
       // moves right
       else if (begin.second < end.second) {
        dir.second = 1;
        rook = getRook(king->getCoords(), RIGHT, whosTurn);
        direction = RIGHT;
       }
       else {return garbage;}
    }
    else if (begin.second == end.second && abs(begin.first - end.first) == 2) {
        dir.second = 0;
        // moves up
        if (begin.first > end.first) {
            dir.first = 1;
            rook = getRook(king->getCoords(), UP, whosTurn);
            direction = UP;
        }
        // moves down
        else if (begin.first < end.first) {
            dir.first = -1;
            rook = getRook(king->getCoords(), DOWN, whosTurn);
            direction = DOWN;
        }
        else {return garbage;}
    }
    else {return garbage;}


    // piece is not king                       king not first move      rook DNE               rook not first move
    if (king->getType() != PieceName::King || !king->getIsFirstMove() || rook == nullptr || !rook->getIsFirstMove()) return garbage;
    
    // check if the position after castling leads to check
    if (isCheck(end)) return garbage;

    pair<int, int> pos = begin;
    for (int i = 0; i < 2; ++i) {
        if (isCheck(pos)) return garbage;
        pos.first += dir.first;
        pos.second += dir.second;
        if (hasObstacle(pos)) return garbage;
    }
    return direction;
}

void Board::move(pair<int, int> &begin, pair<int, int> &end, char prom, MoveType type, char dir) {
    cout << 1 << endl;
    shared_ptr<Piece> p = getPieceAt(begin);
    if (p == nullptr) cout << 2 << endl;
    cout << getPieceAt(begin)->getCoords().first << ", " << getPieceAt(begin)->getCoords().second << endl;


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

    simulate(begin, end, type, prom, dir);

    // check for if the move will lead to checkmate
    if (isCheck(getKing()->getCoords())) {
        undoMove(totalMoves.back());
        throw runtime_error("You cannot move your king into" );
    }
    p->setIsFirstMove();
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
        // modify the coordinate for m.captured
        pair<int, int> tmpCoords = m.captured->getCoords();
        theBoard[tmpCoords.first][tmpCoords.second] = m.captured;

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
            if ((m.to.second - m.from.second) < 0) {
                // rook moved to the left

                // move king to the left
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first, m.to.second + 1));
                theBoard[m.to.first][m.to.second + 1] = nullptr;
                theBoard[m.to.first][m.to.second - 1] = king;
                king->modifyCoords(make_pair(m.to.first, m.to.second - 1));
            }
            else {
                // rook moved to the right

                // move king to the right
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first, m.to.second - 1));
                theBoard[m.to.first][m.to.second - 1] = nullptr;
                theBoard[m.to.first][m.to.second + 1] = king;
                king->modifyCoords(make_pair(m.to.first, m.to.second + 1));
            }
        }
        else {
            // vertical casting (m.to.second == m.from.second)
            if ((m.to.first - m.from.first) < 0) {
                // rook moved down

                // move king down
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first - 1, m.to.second));
                theBoard[m.to.first - 1][m.to.second] = nullptr;
                theBoard[m.to.first + 1][m.to.second] = king;
                king->modifyCoords(make_pair(m.to.first + 1, m.to.second));
            }
            else {
                // rook moved up

                // move king up two squares
                shared_ptr<Piece> king = getPieceAt(make_pair(m.to.first + 1, m.to.second));
                theBoard[m.to.first + 1][m.to.second] = nullptr;
                theBoard[m.to.first - 1][m.to.second] = king;
                king->modifyCoords(make_pair(m.to.first - 1, m.to.second));
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

            shared_ptr<Piece> tmp = m.captured;
            pair<int, int> capCoords = m.captured->getCoords();
            // modify coords for the captured piece
            theBoard[capCoords.first][capCoords.second] = tmp;

            if (m.moving->getColour() == Colour::White) {
                // promoted piece is white hence captured piece is black
                addPiece(m.from, 'P');
                blackPieces.push_back(tmp);
            } else {
                // promoted piece is black hence captured piece is white
                addPiece(m.from, 'p');
                whitePieces.push_back(tmp);
            }
        }
    }
    if (m.tactic == MoveType::Capture) {
        // modify coords for the moving piece
        theBoard[m.from.first][m.from.second] = m.moving;
        theBoard[m.to.first][m.to.second] = nullptr;

        shared_ptr<Piece> tmp = m.captured;
        pair<int, int> capCoords = m.captured->getCoords();
        // modify coords for the captured piece
        theBoard[capCoords.first][capCoords.second] = tmp;

        // push back to the pieces
        if (tmp->getColour() == Colour::White) {
            whitePieces.push_back(tmp);
        }
        else {
            blackPieces.push_back(tmp);
        }
    }
    m.moving->modifyCoords(make_pair(m.from.first,m.from.second));
    totalMoves.pop_back();
}

bool Board::isBlackTurn() {
    if (whosTurn == Colour::Black) return true;
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

void printposmoves(vector<pair<int, int>> moves) {
    for (auto &move : moves) {
        cout << move.first << ", " << move.second << endl;
    }
}

bool contains(vector<pair<int, int>> moves, pair<int, int> move) {
    for (auto& m : moves) {
        if (m.first == move.first && m.second == move.second) return true;
    }
    return false;
}

bool Board::isCheck(pair<int, int> kingPos) {
    if (whosTurn == Colour::Black)  {
        for (auto &p : whitePieces) {
            vector<pair<int, int>> moves = p->getPosMoves();
            if ((!moves.empty()) && (count(moves.begin(), moves.end(), kingPos) > 0)) {
                return true;
            }
        }
    } else {
        for (auto &p : blackPieces) {
            vector<pair<int, int>> moves = p->getPosMoves();
            printposmoves(moves);
            if ((!moves.empty()) && (count(moves.begin(), moves.end(), kingPos) > 0)) {
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
    if (whosTurn == Colour::White) {
        cout << "white" << endl;
    } else {
        cout << "black" << endl;
    }
    if (!isCheck(getKing()->getCoords())) return false;
    for (auto &cells : getKing()->getPosMoves()) {
        if (!isCheck(cells)) return false;
    }
    return true;
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

int Board::moveCount() {
    return totalMoves.size();
}

bool Board::isStalemate() {
    vector<pair<shared_ptr<Piece>, pair<int, int>>> possibleMoves = getAllValidMoves(!isBlackTurn());
    //printMoves(possibleMoves);
    for (auto &m : possibleMoves) {
        pair<int, int> fromCoords = m.first->getCoords();
        pair<int, int> toCoords = m.second;
        char dir = canCastle(fromCoords, toCoords);
        if (dir != ' ') {
            simulate(fromCoords, toCoords, MoveType::Castling, dir);
        }
        else if (canEP(fromCoords, toCoords)) {
            simulate(fromCoords, toCoords, MoveType::EnPassant);
        }
        else if (hasObstacle(toCoords)) {
            simulate(fromCoords, toCoords, MoveType::Capture);
        }
        else {
            simulate(fromCoords, toCoords, MoveType::Normal);
        }
        pair<int, int> kingCoords = getKing()->getCoords();
        if (!isCheck(kingCoords)) {
            undoMove(totalMoves.back());
            // there is a possible move
            return false;
        } else {
            undoMove(totalMoves.back());
        }
    }
    return true;

}
