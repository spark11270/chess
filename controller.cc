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

Controller::Controller(Board* board) : board{board} {}

<<<<<<< Updated upstream
initPlayer(const string& player, Colour colour) {
=======
// ----------------------- Helper ----------------------------
pair<int,int> convertPos(string &pos) {
    int row = stoi(pos[1]) - 1;
    char colInChar = pos[0] - (pos[0] - '0');
    int col = stoi(colInChar);
    return make_pair(row,col);
    
}

// -----------------------------------------------------------


void Controller::initPlayer(const string& player, Colour colour) {
>>>>>>> Stashed changes
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

                while(cin >> command) {
                    try {

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