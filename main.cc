#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"

using namespace std;

int main () { 
  string command;
  
  Board *board;
  TextDisplay *td;

  bool inGame = false;
  bool inSetup = false;

  // Still need to consider exception handling and mispelled commands
  // There are many missing things in main but this should be enough to get started
  while (cin >> command) {
    if (inGame) {
      if (command == "move") {
        string from, to;
        cin >> from >> to;
        // move piece on board
        // For pawn promotion we can take cin from the promotion function 

        // Print board after each move
        //board->render();
      } else if (command == "resign") {
        // End game
        // Make sure board gets deleted
        inGame = false;
      }
    } 
    if (inSetup) {
      if (command == "+") {
        char piece;
        string pos;
        cin >> piece >> pos;
        // Add to board
      } else if (command == "-") {
        string pos;
        cin >> pos;
        // Remove from board
      } else if (command == "=") {
        string color;
        cin >> color;
        // Make the input color go next
      } else if (command == "done") {
        // End setup mode
        // Make sure board gets deleted
        inSetup = false;
      }
    }
    
    // Make sure we don't have inGame and inSetup both true
    if (command == "game") {
      string white, black;
      cin >> white >> black;

      // Declare game board
      board = new Board();

      td = new TextDisplay(board);

      // Render board (both text and graphically)
      //board->render();

      inGame = true;

    } else if (command == "setup") {
      // Declare setup board
      // Render board (both text and graphically)
      inSetup = true;
    }
  }
}
