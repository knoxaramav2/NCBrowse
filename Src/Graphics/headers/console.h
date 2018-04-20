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

class Console{

    WINDOW * _main;
    WINDOW * _toolbar;
    WINDOW * _status;
    WINDOW * _util;

    public:

    Console();
    ~Console();

    Key getKey();

};

extern Console * _terminal;

Console * getTerminal();

//}

#endif