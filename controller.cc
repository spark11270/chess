#include "controller.h"
#include "player.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ----------------------- Helper ----------------------------

// pair<int,int> convertPos(string &pos) {
//     int row = stoi(pos[1]) - 1;
//     char colInChar = pos[0] - (pos[0] - '0');
//     int col = stoi(colInChar);
//     return make_pair(row,col);
    
// }

// bool uniqueKing(board *b) {
//     pair<int, int>  kingCount = make_pair(0, 0); // pair<white, black>
//     for (auto &piece : whitePieces) {
//         if (piece->getPiece() == PieceName::King) {
//             ++kingCount.first();
//         }
//     }
//     for (auot &piece : blackPieces) {
//         ++kingCount.second();
//     }

//     if (kingCount.second == 1 && kingCount.first == 1) return true;
//     return false;

// }

// bool validPawns(board *b) {
//     for (auto &piece : whitePieces) {
//         if (piece->getPiece() == PieceName::Pawn) {
//             if (piece->getCoor().first == 7) return false;
//         }
//     }

//     for (auto &piece : blackPieces) {
//         if (piece->getPiece() == PieceName::Pawn) {
//             if (piece->getCoor().first == 0) return false;
//         }
//     }
// }

// // -----------------------------------------------------------

Controller::Controller(Board* board) : board{board} {}

// initPlayer(const string& player, Colour colour) {
//     if (colour == Colour::White) {
//         if (player == "human") player.push_back(make_unique<Human>(Colour::White));
//         if (player == "computer1") player.push_back(make_unique<Computer>(Colour::White, 1));
//         if (player == "computer2") player.push_back(make_unique<Computer>(Colour::White, 2));
//         if (player == "computer3") player.push_back(make_unique<Computer>(Colour::White, 3));
//         if (player == "computer4") player.push_back(make_unique<Computer>(Colour::White, 4));
//     }
//     if (colour == Colour::Black) {
//         if (player == "human") player.push_back(make_unique<Human>(Colour::Black));
//         if (player == "computer1") player.push_back(make_unique<Computer>(Colour::Black, 1));
//         if (player == "computer2") player.push_back(make_unique<Computer>(Colour::Black, 2));
//         if (player == "computer3") player.push_back(make_unique<Computer>(Colour::Black, 3));
//         if (player == "computer4") player.push_back(make_unique<Computer>(Colour::Black, 4));
//     }
//     else {
//         throw runtime_error("Please enter a valid player: Human / Computer[1-4]");
//     }
// }

// void Controller::initGame() {
//     while(cin >> command) {
//         string piece;
//         string pos;
//         string player;
//         try {
//             if (command == "+") {
//                 cin >> piece;
//                 cin >> pos;
//                 pair<int, int> coords = convertPos(pos);
//                 board->addPiece(piece, coords);
//                 board->render();
//             }
//             else if (command == "-") {
//                 cin >> pos;
//                 pair<int, int> coords = convertPos(pos);
//                 board->removePieceAt(coords);
//                 board->render;
//             }
//             else if (command == "=") {
//                 cin >> player;
//                 if (player == "black") board->setPlayerFirst(Colour::black);
//                 if (player == "white") board->setPlayerFirst(Colour::white);
//                 else {
//                     throw runtime_error("Please enter a valid colour");
//                 }
//             }
//             else if (command == "done") {
//                 if (board->uniqueKing == false) throw runtime_error("You must have one kings for each player");
//                 else if (board->validPawns == false) throw runtime_error("You must not have Pawns on first and last row");
//                 else {
//                     doneSetup = true;
//                     cout << "EXIT SETUP MODE" << endl;
//                     break;
//                 }
//             }
//             else {
//                 throw runtime_error("Please enter a valid command for the setup");
//             }
//         }
//         catch (runtime_error &f) {
//             cerr << f.what() << endl;
//         } 
//     }

// }

// void Controller::playGame() {
//     string command;
//     while(cin >> command) {
//         try {
//             if (command == "setup") {
//                 try {
//                     cout << "IN SETUP MODE" << endl;
//                     if (inGame == true) {
//                     throw runtime_error("Game is currently running");
//                     }
//                     o.push_back(TextObserver(board));
//                     o.push_back(GraphicsObesrver(board));
//                     board->render;
//                     initGame();
//                 }
//                 catch {
//                     cerr << f.what() << endl;
//                     break;

//                 }     
//             }
//             else if (command == "game") {
//                 if (doneSetup == false) board->init();
//                 inGame = true;
//                 string wPlayer, bPlayer;
//                 ss >> wPlayer;
//                 ss >> bPlayer;
//                 initPlayer(wPlayer, Coluor::White);
//                 initPlayer(bPlayer, Colour::Black);
//                 gameMoves();
//             }
//             else {
//                 throw runtime_error("Please enter a valid command");
//             }
//         }
//         catch (runtime_error &f) {
//             cerr << f.what() << endl;
//         } 
//     }
// }

void Controller::gameMoves() {
    board->init();
    board->render();
    // string line;
    // string command;
    // while (getline(cin, line)) {
    //     istringstream ss{line};
    //     line >> command;
    //     try {
    //         if (command == "resign") {
    //             if (board->isWhiteTurn()) {
    //                 // black resigns
    //                 player[0]->updateScore();
    //             }
    //             else {
    //                 // white resigns
    //                 player[1]->updateScore();
    //             }
    //         }
    //         else if (command == "move") {
    //             line = command + " " + line;
    //             if (board->isWhiteTurn() == true) {
                    
    //             }
    //             else {

    //             }
    //         }
    //         else {
    //             throw runtime_error("Please enter a valid command");
    //         }
    //     }
    //     catch (runtime_error &f){
    //         cerr << f.what() << endl;
    //     }
    // }
}