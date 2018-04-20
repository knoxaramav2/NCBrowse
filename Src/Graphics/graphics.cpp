#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include "graphics.h"

using namespace std;
//using namespace CONSOLE;

Console * _terminal;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup(){
    cout << "LOADED GRAPHICS" << endl;

    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    cbreak();
}

void shutdown(){
    endwin();
}