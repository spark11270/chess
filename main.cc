#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "controller.h"

using namespace std;

int main () { 
  Board *theboard = new Board();
  TextDisplay td{theboard};
  Controller ctr{theboard};
  ctr.playGame();
}
