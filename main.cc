#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"

using namespace std;

int main () { 
  string command;
  
  Board *board;

  bool inGame = false;
  bool inSetup = false;

  // Still need to consider exception handling and mispelled commands
  while (cin >> command) {
    if (inGame) {
      if (command == "move") {
        string from, to;
        cin >> from >> to;
        // move piece on board
        // For pawn promotion we can take cin from the promotion function
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

      // Render board (both text and graphically)
      board->render();

      inGame = true;

    } else if (command == "setup") {
      // Declare setup board
      // Render board (both text and graphically)
      inSetup = true;
    }
  }
}
