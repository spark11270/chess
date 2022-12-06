#ifndef XWINDOWS_H
#define XWINDOWS_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  // Available colours.
  enum {White=0, Black, Red, Brown, Blue, Cyan, Yellow, Magenta, Orange, Green};

  void drawImage(int x, int y, char* bmp);
  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour);

  // Draws a string
  void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);
  void drawString(int x, int y, std::string msg);

  void drawBigString(int x, int y, std::string msg, int colour);

  void drawBoard();
};


#endif
