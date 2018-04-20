#ifndef GRAPHICS_CONSOLE
#define GRAPHICS_CONSOLE

#include "ncurses.h"

//namespace CONSOLE{

enum KeyType{
    ascii,
    fkey,
    upper,
    arrow
};

struct Key{
    int key;
    KeyType type;
};

struct Coord{
    int x;
    int y;
};

class Panel{
    WINDOW * _win;
    int _x, _y, _width, _height;

    public:

    Panel();
    Panel(int, int, int, int);
    ~Panel();
};

class Console{

    Panel _main;
    Panel _toolbar;
    Panel _status;
    Panel _util;

    public:

    Console();
    ~Console();

    void resize();

    Key getKey();

};

extern Console * _terminal;

Console * getTerminal();
Coord getMouseLoc();

//}

#endif