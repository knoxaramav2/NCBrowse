#include "console.h"

//using namespace CONSOLE;

//Console * _terminal;

Panel::Panel(){

}

Panel::Panel(int x, int y, int w, int h){
    _x = x;
    _y = y;
    _width = w;
    _height = h;
}

Panel::~Panel(){

}


Console::Console(){

}

Console::~Console(){

}

void Console::resize(){

}

Key Console::getKey(){
    int i = getch();
    KeyType kt = KeyType::ascii;

    return Key{.key = i, .type = kt};
}


Console * getTerminal(){
    return _terminal;
}

Coord getMouseLoc(){
    Coord c;
    MEVENT event;

    bool i = getmouse(&event) == OK; 

    c.x = event.x + 1;
    c.y = event.y + 1;

    return c;
}