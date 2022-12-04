#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "xwindow.h"
#include <sstream>
#include <cstring>

using namespace std;

Xwindow::Xwindow(int width, int height) {

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);

  // Make sure we don't race against the Window being shown
  XEvent ev;
  while(1) {
    XNextEvent(d, &ev);
    if(ev.type == Expose) break;
  }
}

Xwindow::~Xwindow() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::printMessage(int x, int y, const string& msg, int colour, XFontStruct& f){
  XSetForeground(d, gc, colours[colour]);
  XTextItem ti;
  ti.chars = const_cast<char*>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f.fid;
  XDrawText(d, w, gc, x, y, &ti, 1);
  XSetForeground(d, gc, colours[Black]);
  XFlush(d);
}

void Xwindow::drawString(int x, int y, std::string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void Xwindow::drawBigString(int x, int y, std::string msg, int colour) {
	int width = 450;
	int height = 450;
	std::ostringstream name;
	name << "-*-helvetica-bold-r-*-*-*-240-" << width/5 << "-" << height/5 << "-*-*-*-*";
	XFontStruct * f = XLoadQueryFont(d, name.str().c_str());	

        if ( f == nullptr ){
                f = XLoadQueryFont(d, "6x13");
        }


	printMessage(x, y, msg, colour, *f);
	delete f;
}

void Xwindow::drawBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->fillRectangle((1+(i+1)%2)*50+j*100, 50*i, 50, 50, Xwindow::Black);
		}
	}
	for (int i = 0; i < 8; i++) {
		std::stringstream stream;
		stream << 8-i;
		std::string s;
		stream >> s;
		this->drawBigString(15, 35+i*50, s, Xwindow::Black);
	}
	/*
	std::string alphabet = "ABCDEFGH";
	int i = 0;
	for( char c : alphabet) {
		std::string s(c);
		this->drawBigString(65+i*50, 435, s);
		i++;
	}
	*/
	this->drawBigString(65+0*50, 435, "A", Xwindow::Black);
	this->drawBigString(65+1*50, 435, "B", Xwindow::Black);
	this->drawBigString(65+2*50, 435, "C", Xwindow::Black);
	this->drawBigString(65+3*50, 435, "D", Xwindow::Black);
	this->drawBigString(65+4*50, 435, "E", Xwindow::Black);
	this->drawBigString(65+5*50, 435, "F", Xwindow::Black);
	this->drawBigString(65+6*50, 435, "G", Xwindow::Black);
	this->drawBigString(65+7*50, 435, "H", Xwindow::Black);
}
	
