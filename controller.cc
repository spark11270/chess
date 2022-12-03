#include "controller.h"
#include "xwindow.h"
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
                switch(piece) {
                    case 'K':
                        thePiece = make_shared<King>(Colour::White, coords.first, coords.second);
                        break;
                    case 'Q':
                        thePiece = make_shared<Queen>(Colour::White, coords.first, coords.second);
                        break;
                    case 'N':
                        thePiece = make_shared<Knight>(Colour::White, coords.first, coords.second);
                        break;
                    case 'B':
                        thePiece = make_shared<Bishop>(Colour::White, coords.first, coords.second);
                        break;
                    case 'R':
                        thePiece = make_shared<Rook>(Colour::White, coords.first, coords.second);
                        break;
                    case 'P': 
                        thePiece = make_shared<Pawn>(Colour::White, coords.first, coords.second);
                        break;
                    case 'k':
                        thePiece = make_shared<King>(Colour::Black, coords.first, coords.second);
                        break;
                    case 'q':
                        thePiece = make_shared<Queen>(Colour::Black, coords.first, coords.second);
                        break;
                    case 'n':
                        thePiece = make_shared<Knight>(Colour::Black, coords.first, coords.second);
                        break;
                    case 'b':
                        thePiece = make_shared<Bishop>(Colour::Black, coords.first, coords.second);
                        break;
                    case 'r':
                        thePiece = make_shared<Rook>(Colour::Black, coords.first, coords.second);
                        break;
                    case 'p':
                        thePiece = make_shared<Pawn>(Colour::Black, coords.first, coords.second);
                        break;
                }
                board->addPiece(thePiece);
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
                board->render();
                gameMoves();
                Xwindow w(450, 450);
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
                if (board->isWhiteTurn() == true) {
                    if(players[0]->getType() == 'c') {
                        // board->move();
                        // board->render();
                        // continue;
                    }
                    else {
                        ss >> from;
                        pair<int, int> fromCoords = convertPos(from);
                        ss >> to;
                        pair<int, int> toCoords = convertPos(to);
                        if (ss >> prom) {
                            // handle promotion
                            cout << prom << endl;
                        }
                        else {
                            // no promotion
                            board->move(fromCoords, toCoords, Colour::White);
                        }
                    }
                }
                else {
                    if(players[1]->getType() == 'c') {
                        // board->move();
                        // board->render();
                        // continue;
                    }
                    else {
                        ss >> from;
                        pair<int, int> fromCoords = convertPos(from);
                        ss >> to;
                        pair<int, int> toCoords = convertPos(to);
                        if (ss >> prom) {
                            // handle promotion
                            cout << prom << endl;
                        }
                        else {
                            // no promotion
                            board->move(fromCoords, toCoords, Colour::Black);
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
