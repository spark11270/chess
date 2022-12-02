#include "controller.h"
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
    char c = pos[0] - ('a' - '0');
    cout << c << endl;
    switch(pos[1]) {
        case 'a':
            return make_pair(0, (int)pos[1]);
            break;
        case 'b':
            return make_pair(1, (int)pos[1]);
            break;
        case 'c':
            return make_pair(2, (int)pos[1]);
            break;
        case 'd':
            return make_pair(3, (int)pos[1]);
            break;
        case 'e':
            return make_pair(4, (int)pos[1]);
            break;
        case 'f':
            return make_pair(5, (int)pos[1]);
            break;
        case 'g':
            return make_pair(6, (int)pos[1]);
            break;
        case 'h':
            return make_pair(7, (int)pos[1]);
            break;
        
    }
    // int row = (int)pos[1] - 1;
    // char colInChar = pos[0] - 43;
    // cout << colInChar;
    // int col = (int)colInChar;
    // return make_pair(row,col);
}

// -----------------------------------------------------------

Controller::Controller(Board* board) : board{board}, inGame{false}, doneSetup{false} {}

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
        string player;
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
                cin >> player;
                if (player == "black") board->setPlayerFirst(Colour::Black);
                if (player == "white") board->setPlayerFirst(Colour::White);
                else {
                    throw runtime_error("Please enter a valid colour");
                }
            }
            else if (command == "done") {
                if (board->uniqueKing() == false) throw runtime_error("You must have one kings for each player");
                else if (board->validPawns() == false) throw runtime_error("You must not have Pawns on first and last row");
                else {
                    doneSetup = true;
                    cout << "EXIT SETUP MODE" << endl;
                    break;
                }
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
                cout << wPlayer << endl;
                initPlayer(wPlayer, Colour::White);
                cin >> bPlayer;
                cout << bPlayer << endl;
                initPlayer(bPlayer, Colour::Black);
                gameMoves();
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
    while (getline(cin, line)) {
        istringstream ss{line};
        ss >> command;
        try {
            if (command == "resign") {
                if (board->isWhiteTurn()) {
                    // black resigns
                    players[0]->updateScore();
                }
                else {
                    // white resigns
                    players[1]->updateScore();
                }
            }
            else if (command == "move") {
                if (board->isWhiteTurn() == true) {
                    if(players[0]->getType() == 'c') {
                        // board->move();
                        // continue;
                    }
                    cin >> from;
                    pair<int, int> fromCoords = convertPos(from);
                    cin >> to;
                    pair<int, int> toCoords = convertPos(to);
                    board->move(fromCoords, toCoords, Colour::White);
                }
                else {
                    // black's turn
                    cin >> from;
                    pair<int, int> fromCoords = convertPos(from);
                    cin >> to;
                    pair<int, int> toCoords = convertPos(to);
                    board->move(fromCoords, toCoords, Colour::Black);
                }
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