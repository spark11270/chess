#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "controller.h"
#include "xwindow.h"

using namespace std;

int main () { 
  Board *theboard = new Board();
  TextDisplay td{theboard};
  //GraphicsDisplay gd{theboard};
  theboard->render();
  Controller ctr{theboard};
  ctr.playGame();
}
