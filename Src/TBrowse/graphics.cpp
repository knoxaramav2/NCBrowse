#include <sys/ioctl.h>
#include <stdio.h>

#include "graphics.h"

Console * _terminal = nullptr;

Panel::Panel(){

    _selected = false;

    _x=_y=_width=_height=5;
    _win = newwin(_height,_width,0,0);
}

Panel::Panel(int x, int y, int w, int h){

    _selected = false;

    _x = x;
    _y = y;
    _width = w;
    _height = h;

    _win = newwin(h,w,y,x);
}

Panel::~Panel(){
    
    _clearBorder();

    delwin(_win);
    _win = nullptr;
}

void Panel::_clearBorder(){
    //wborder(_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    //wrefresh(_win);
}

void Panel::_paintBorder(){
    if (!_selected)
        box(_win, 0, 0);
    else 
        box(_win, '*', '*');
    wrefresh(_win);
}

void Panel::clear(){
    //wclear(_win);
    wrefresh(_win);
}

void Panel::moveTo(int x, int y){
    wclear(_win);
    if (mvwin(_win, y, x) != OK)
        return;
    _x = x;
    _y = y;
    paint();
}

void Panel::resize(int w, int h){
    wresize(_win, h, w);

    _width = w;
    _height = h;
}

void Panel::paint(){
    if (_win == nullptr)
        return;
    _paintBorder();
    wrefresh(_win);
}

void Panel::setSelect(bool selected){

    _selected = selected;

    _clearBorder();
    _paintBorder();
}


Console::Console(){

    resize();

    _selected = 0;
    _selectPanel(WIN_MAIN);

    render();
}

Console::~Console(){
    endwin();
}

void Console::_selectPanel(int select){
    if (select < 0 || select >= 4)
        return;
    
    _panels[_selected].setSelect(false);
    _panels[select].setSelect(true);
    _selected = select;
    _panels[select].paint();
    refresh();
}

void Console::resize(){
    WinInfo wi = getTermDim();

    const int BAR_HEIGHT = 4;
    const int SB_WIDTH = 10;
    
    _panels[WIN_SIDE].resize(SB_WIDTH, wi.h);
    _panels[WIN_SIDE].moveTo(0, 0);

    _panels[WIN_TOOL].resize(wi.w - SB_WIDTH, BAR_HEIGHT);
    _panels[WIN_TOOL].moveTo(SB_WIDTH, 0);

    _panels[WIN_STAT].resize(wi.w - SB_WIDTH, BAR_HEIGHT);
    _panels[WIN_STAT].moveTo(SB_WIDTH, wi.h-BAR_HEIGHT);

    _panels[WIN_MAIN].resize(wi.w - SB_WIDTH, wi.h - (2*BAR_HEIGHT));
    _panels[WIN_MAIN].moveTo(SB_WIDTH, BAR_HEIGHT);
}

void Console::render(){
    for (int i = 0; i < 4; ++i){
        _panels[i].clear();
        _panels[i].paint();
    }
        
}

void Console::clearAll(){

}

void Console::clearPanel(int p){
    if (p<0 || p>=4)
        return;
    _panels[p].clear();
}

void Console::focusNext(){

    _panels[_selected].setSelect(false);

    if (_selected == WIN_STAT){
        _selected = WIN_MAIN;
    } else {
        ++_selected;
    }

    _panels[_selected].setSelect(true);
}

void Console::focusPrev(){
    _panels[_selected].setSelect(false);

    if (_selected == WIN_MAIN){
        _selected = WIN_STAT;
    } else {
        --_selected;
    }

    _panels[_selected].setSelect(true);
}

WinInfo Console::getTermDim(){

    struct winsize sz;
    WinInfo wi {
        .x=-1,
        .y=-1,
        .w=-1,
        .h=-1
    };

    if (ioctl(0, TIOCGWINSZ, (char*) &sz) < 0)
        return wi;

    return WinInfo{
        .x=-1,
        .y=-1,
        .w = sz.ws_col,
        .h = sz.ws_row
    };
}

Key Console::getKey(){
    int i = getch();
    KeyType kt = KeyType::ascii;

    return Key{.key = i, .type = kt};
}

void initTerminal(){
    if (_terminal != nullptr)
        return;

    initscr();
    start_color();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);
    refresh();

    _terminal = new Console();

}

Console * getTerminal(){
    return _terminal;
}
