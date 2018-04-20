#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include "graphics.h"

using namespace std;
//using namespace CONSOLE;

Console * _terminal;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void initColors(){
    for (int fc = COLOR_BLACK; fc <= COLOR_WHITE; ++fc)
        for (int bc = COLOR_BLACK; bc <= COLOR_WHITE; ++bc)
            init_pair((fc * 8) + bc, fc, bc);
}

void startup(){
    cout << "LOADED GRAPHICS" << endl;

    initscr();
    start_color();
    raw();
    noecho();
    keypad(stdscr, true);
    cbreak();

    initColors();

}

void shutdown(){
    endwin();
}