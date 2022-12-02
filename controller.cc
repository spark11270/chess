#include "controller.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Controller::Controller(Board* board) : board{board} {}

// ----------------------- Helper ----------------------------
pair<int,int> convertPos(string &pos) {
    int row = stoi(pos[1]) - 1;
    char colInChar = pos[0] - (pos[0] - '0');
    int col = stoi(colInChar);
    return make_pair(row,col);
    
}


void Controller::initPlayer(const string& player, Colour colour) {
    if (colour == Colour::White) {
        if (player == "human") player.push_back(make_unique<Human>(Colour::White));
        if (player == "computer1") player.push_back(make_unique<Computer>(Colour::White, 1));
        if (player == "computer2") player.push_back(make_unique<Computer>(Colour::White, 2));
        if (player == "computer3") player.push_back(make_unique<Computer>(Colour::White, 3));
        if (player == "computer4") player.push_back(make_unique<Computer>(Colour::White, 4));
    }
    if (colour == Colour::Black) {
        if (player == "human") player.push_back(make_unique<Human>(Colour::Black));
        if (player == "computer1") player.push_back(make_unique<Computer>(Colour::Black, 1));
        if (player == "computer2") player.push_back(make_unique<Computer>(Colour::Black, 2));
        if (player == "computer3") player.push_back(make_unique<Computer>(Colour::Black, 3));
        if (player == "computer4") player.push_back(make_unique<Computer>(Colour::Black, 4));
    }
    else {
        throw runtime_error("Please enter a valid player: Human / Computer[1-4]");
    }
}



void Controller::playGame() {
    string line;
    string command;
    while(getline(cine, line)) {
        try {
            istringstream ss{line};
            ss >> command;
            if (command == "game") {
                string wPlayer, bPlayer;
                ss >> wPlayer;
                ss >> bPlayer;
                initPlayer(wPlayer, Coluor::White);
                initPlayer(bPlayer, Colour::Black);
            }
            if (command == "setup") {
                if (inGame) throw runtime_error("Game is currently running");
                o.push_back(TextObserver(board));
                o.push_back(GraphicsObesrver(board));
                board->render;

                while(cin >> command) {
                    try {
                        if (command == "+") {
                            string piece;
                            string pos;
                            cin >> piece;
                            cin >> pos;
                            pair<int, int> coords = convertPos(pos);
                            

                        }
                    }
                    
                }

                
            }

        }
        
    }
    catch (runtime_error &f) {
        cerr << f.what() << endl;
    }
    


}