#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "controller.h"

using namespace std;

int main () { 
  Board *theboard = new Board();
  theboard->init();
  TextDisplay td{theboard};
  theboard->render();
}
