#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "controller.h"

using namespace std;

int main () { 
  std::shared_ptr<Board> theboard = make_shared<Board>();
  theboard->render();
  Controller ctr{theboard};
  ctr.playGame();
}
