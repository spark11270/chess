#include "controller.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "board.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h"
#include "human.h"
#include "computer.h"

using namespace std;

// ----------------------- Helper ----------------------------

pair<int,int> convertPos(string &pos) {
    if (pos[0] < 'a' || pos[0] > 'h') throw runtime_error("invalid position entered: " + pos);
    if (pos[1] < '1' || pos[1] > '8') throw runtime_error("invalid position entered: " + pos);

    char c = pos[0] - ('a' - '0');
    int col = c - '0';
    int row = 7 - (pos[1] - '0' - 1);

    return make_pair(row,col);
}

// -----------------------------------------------------------

Controller::Controller(Board* board) : board{board}, inGame{false}, doneSetup{false}, rounds{0} {}

void Controller::initPlayer(const string& player, Colour colour) {
    if (colour == Colour::White) {
        if (player == "human") {
            players.push_back(make_unique<Human>(Colour::White));
        } else if (player == "computer1") {
            players.push_back(make_unique<Computer>(Colour::White, 1));
        } else if (player == "computer2") {
            players.push_back(make_unique<Computer>(Colour::White, 2));
        } else if (player == "computer3") {
            players.push_back(make_unique<Computer>(Colour::White, 3));
        } else {
            if (player == "computer4") {
            players.push_back(make_unique<Computer>(Colour::White, 4));
            }
        }
    } else if (colour == Colour::Black) {
        if (player == "human") {
            players.push_back(make_unique<Human>(Colour::Black));
        } else if (player == "computer1") {
            players.push_back(make_unique<Computer>(Colour::Black, 1));
        } else if (player == "computer2") {
            players.push_back(make_unique<Computer>(Colour::Black, 2));
        }
        else if (player == "computer3") {
            players.push_back(make_unique<Computer>(Colour::Black, 3));
        }
        else {
            if (player == "computer4") {
            players.push_back(make_unique<Computer>(Colour::Black, 4));
            }
        }
    } else {
        throw runtime_error("Please enter a valid player: Human / Computer[1-4]");
    }
}

void Controller::initGame() {
    string command;
    while(cin >> command) {
        char piece;
        string pos;
        string colour;
        try {
            if (command == "+") {
                cin >> piece;
                cin >> pos;
                shared_ptr<Piece> thePiece;
                pair<int, int> coords = convertPos(pos);
                board->addPiece(coords, piece);
                board->render();
            }
            else if (command == "-") {
                cin >> pos;
                pair<int, int> coords = convertPos(pos);
                board->removePieceAt(coords);
                board->render();
            }
            else if (command == "=") {
                cin >> colour;
                if (colour == "black") board->setPlayerFirst(Colour::Black);
                else if (colour == "white") board->setPlayerFirst(Colour::White);
                else {
                    throw runtime_error("Please enter a valid colour");
                }
            }
            else if (command == "done") {
                if (board->uniqueKing() == false) {
                    throw runtime_error("You must have one kings for each player");
                }
                if (board->validPawns() == false) {
                    throw runtime_error("You must not have Pawns on first and last row");
                }
                if (board->isCheck(board->getKing()->getCoords())) {
                    if (board->getWhosTurn() == Colour::White) {
                        throw runtime_error("White King is in check");
                    } else {
                        throw runtime_error("Black King is in check");
                    }
                }
                doneSetup = true;
                cout << "EXIT SETUP MODE" << endl;
                break;
            }
            else {
                throw runtime_error("Please enter a valid command for the setup");
            }
        }
        catch (runtime_error &f) {
            cerr << f.what() << endl;
        } 
    }

 }

void Controller::playGame() {
    string command;
    while(cin >> command) {
        try {
            if (command == "setup") {
                try {
                    cout << "IN SETUP MODE" << endl;
                    if (inGame == true) {
                    throw runtime_error("Game is currently running");
                    }
                    board->render();
                    initGame();
                }
                catch (runtime_error &f) {
                    cerr << f.what() << endl;
                    break;

                }     
            }
            else if (command == "game") {
                if (doneSetup == false) board->init();
                inGame = true;
                string wPlayer, bPlayer;
                cin >> wPlayer;
                initPlayer(wPlayer, Colour::White);
                cin >> bPlayer;
                initPlayer(bPlayer, Colour::Black);
                
		TextDisplay td{board};
		GraphicsDisplay gd{board};
		board->render();
                
		gameMoves();
                
                if (!newRound) break;
                board->clear();
                doneSetup = false;
                inGame = false;
                for (auto &player : players) {
                    player->resetScore();
                }
            }
            else {
                throw runtime_error("Please enter a valid command: " + command);
            }
        }
        catch (runtime_error &f) {
            cerr << f.what() << endl;
        } 
    }
}


void Controller::gameMoves() {
    string line;
    string command;
    string from;
    string to;
    char prom;

    getline(cin, line); //ignore one newline
    while (getline(cin, line)) {
        try {
        istringstream ss{line};
        ss >> command;
            if (command == "resign") {
                if (board->isWhiteTurn()) {
                    // black resigns
                    cout << "White Wins!" << endl;
                    players[0]->updateScore();
                }
                else {
                    // white resigns
                    cout << "Black Wins!" << endl;
                    players[1]->updateScore();
                }
                printScore();
                break;
            }
            else if (command == "move") {
                if (board->isCheck(board->getKing()->getCoords())) {
                    players[1]->updateScore();
                    printScore();
                    break;
                }
                if (board->isWhiteTurn() == true) {
                    if(players[0]->getType() == 'c') {
                        pair<int, int> uselsssCord = make_pair(-1, -1);
                        players[0]->move(board, uselsssCord, uselsssCord);
                    }
                    else {
                        ss >> from;
                        pair<int, int> fromCoords = convertPos(from);
                        ss >> to;
                        pair<int, int> toCoords = convertPos(to);

                        if (!isValid(fromCoords, toCoords)) {
                            throw runtime_error("Invalid move");
                        }
                        if (board->canEP(fromCoords, toCoords)) {
                            board->move(fromCoords, toCoords, MoveType::EnPassant);
                        } 
                        else if (ss >> prom) {
                            if (board->getPieceAt(fromCoords)->getType() != PieceName::Pawn) {
                                throw runtime_error ("You can only promote Pawn");
                            }
                            if (board->getWhosTurn() == Colour::White) {
                                if (toCoords.first != 0) {
                                    throw runtime_error ("White has not reached into the enemy's back row");
                                }
                            }
                            if (prom == 'k' || prom == 'K') {
                                throw runtime_error("You cannot promote to King");
                            }
                           board->move(fromCoords, toCoords, MoveType::Promotion, prom);
                        } 
                        else {
                            // no promotion
                            if (board->canEP(fromCoords, toCoords)) {
                            board->move(fromCoords, toCoords, MoveType::EnPassant);
                            }
                            if (board->canCastle(fromCoords, toCoords)) {
                                board->move(fromCoords, toCoords, MoveType::Castle);
                            }
                            if (board->hasObstacle(toCoords)) {
                                board->move(fromCoords, toCoords, MoveType::Capture);
                            }
                            else {
                                board->move(fromCoords, toCoords, MoveType::Normal);
                            }
                        }
                    }
                }
                else {
                    if(players[1]->getType() == 'c') {
                        pair<int, int> uselsssCord = make_pair(-1, -1);
                        players[0]->move(board, uselsssCord, uselsssCord);
                    }
                    else {
                        ss >> from;
                        pair<int, int> fromCoords = convertPos(from);
                        ss >> to;
                        pair<int, int> toCoords = convertPos(to);
                        if (ss >> prom) {
                            if (board->getPieceAt(fromCoords)->getType() != PieceName::Pawn) {
                                    throw runtime_error ("You can only promote Pawn");
                            } 
                            if (board->getWhosTurn() == Colour::Black) {
                                if (toCoords.first != 7) {
                                    throw runtime_error ("Black has not reached into the enemy's back row");
                                }
                            }
                            if (prom == 'k' || prom == 'K') {
                                throw runtime_error("You cannot promote to King");
                            }
                            board->move(fromCoords, toCoords, MoveType::Promotion, prom);
                        }
                        else {
                            // no promotion
                            if (board->canEP(fromCoords, toCoords)) {
                            board->move(fromCoords, toCoords, MoveType::EnPassant);
                            }
                            if (board->canCastle(fromCoords, toCoords)) {
                                board->move(fromCoords, toCoords, MoveType::Castle);
                            }
                            board->move(fromCoords, toCoords);
                        }
                    }
                }
                board->render();
            }
            else {
                throw runtime_error("Please enter a valid command");
            }
        }
        catch (runtime_error &f){
            cerr << f.what() << endl;
        }
    }
}

bool Controller::isValid(const pair<int, int> from, const pair<int, int> to) {

    shared_ptr<Piece> p = board->getPieceAt(from);

    if (p == nullptr) { return false; }
    if (p->getColour() != board->getWhosTurn()) {
        throw runtime_error("Wrong player's turn to move");
    }

    return p->isValidMove(from, to);
}

void Controller::printScore() {
    cout << "ROUND " << rounds << endl << endl;
    cout << "Final Score" << endl;
    cout << "White: " << players[0]->getScore() << endl;
    cout << "Black: " << players[1]->getScore() << endl;
    
    char ans;
    cout << "Do you want to play again? [Y/N]" << endl;
    while (true) {
        if (cin.eof()) break;
        cin >> ans;
        while (cin >> ans) {
            continue;
        }
        if (cin.eof()) break;
        if (ans == 'Y') newRound = true;
        if (ans == 'N') newRound = false;
        cout << "Please either choose Y/N" << endl;
    }
}
