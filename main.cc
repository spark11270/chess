#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "controller.h"

using namespace std;

int main () { 
  Board *theboard = new Board();
  theboard->render();
  Controller ctr{theboard};
  ctr.playGame();
  delete theboard;
}
