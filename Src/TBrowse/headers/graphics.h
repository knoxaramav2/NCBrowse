#ifndef GRAPHICS
#define GRAPHICS

#include "ncurses.h"

#define WIN_MAIN 0
#define WIN_TOOL 1
#define WIN_SIDE 2
#define WIN_STAT 3

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

struct WinInfo{
    int x;
    int y;
    int w;
    int h;
};

class Panel{
    WINDOW * _win;
    int _x, _y, _width, _height;

    void _clearBorder();
    void _paintBorder();

    bool _selected;

    public:

    Panel();
    Panel(int, int, int, int);
    ~Panel();

    void clear();
    void moveTo(int, int);
    void resize(int, int);
    void paint();
    void setSelect(bool);
};

class Console{

    Panel _panels[4];
    int _selected;

    void _selectPanel(int);

    public:

    Console();
    ~Console();

    void resize();
    void render();

    void clearAll();
    void clearPanel(int);

    void focusNext();
    void focusPrev();

    static WinInfo getTermDim();
    static Key getKey();
};

extern Console * _terminal;

void initTerminal();

Console * getTerminal();

#endif