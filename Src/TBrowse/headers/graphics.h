#ifndef GRAPHICS
#define GRAPHICS

#include "ncurses.h"

#include "fdom.h"
#include "event.h"

#define WIN_MAIN 0
#define WIN_TOOL 1
#define WIN_SIDE 2
#define WIN_STAT 3

#define COLOR(fg, bg) ((fg << 3) | bg)

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

class Panel : public Actable{

    DOM * _dom;

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
    void arrowDOMTarget(int);

    virtual Event action(Event);

    void renderDOM();
    void setDOM(DOM *);

    DOM * _getDOM();
};

class ContentPanel : public Panel{

    public:

    ContentPanel(int, int, int, int);
    virtual Event action(Event);

};

class StatusPanel : public Panel{
    public:

    StatusPanel(int, int, int, int);
    virtual Event action(Event);
};

class ToolPanel : public Panel{
    public:

    ToolPanel(int, int, int, int);
    virtual Event action(Event);
};

class SidePanel : public Panel{
    public:

    SidePanel(int, int, int, int);
    virtual Event action(Event);
};


class Console{

    Panel * _panels[4];
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

    void wrenderDOM(int);
    void wsetDOM(int, DOM *);

    void action(Event);

    static WinInfo getTermDim();
    static Key getKey();
};

extern Console * _terminal;

void initTerminal();

Console * getTerminal();
void colorOn(WINDOW *, int fg, int bg);
void colorOff(WINDOW *, int fg, int bg);

#endif