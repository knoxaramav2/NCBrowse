#include <sys/ioctl.h>
#include <stdio.h>
#include <vector>

#include "state.h"
#include "browseinfo.h"
#include "graphics.h"

Console * _terminal = nullptr;

DOM * initToolDom();
DOM * updateContentDom(DOM *);

using namespace std;

ContentPanel::ContentPanel(int x, int y, int w, int h) : Panel(x,y,w,h){};
StatusPanel::StatusPanel(int x, int y, int w, int h) : Panel(x,y,w,h){};
ToolPanel::ToolPanel(int x, int y, int w, int h) : Panel(x,y,w,h){};
SidePanel::SidePanel(int x, int y, int w, int h) : Panel(x,y,w,h){};


Event ContentPanel::action(Event e){

    switch(e.val){
        case KEY_UP: arrowDOMTarget(SEL_UP); break;
        case KEY_DOWN: arrowDOMTarget(SEL_DOWN); break;
        case KEY_LEFT: arrowDOMTarget(SEL_LEFT); break;
        case KEY_RIGHT: arrowDOMTarget(SEL_RIGHT); break;
            
        break;
    }

    return Event{.type = NO_ACTION};
}

Event StatusPanel::action(Event e){

    return Event{.type = NO_ACTION};
}

Event ToolPanel::action(Event e){

    switch(e.val){
        case KEY_UP: arrowDOMTarget(SEL_UP); break;
        case KEY_DOWN: arrowDOMTarget(SEL_DOWN); break;
        case KEY_LEFT: arrowDOMTarget(SEL_LEFT); break;
        case KEY_RIGHT: arrowDOMTarget(SEL_RIGHT); break;
        case KEY_ENTER:{
            
        }
        break;
    }

    return Event {.type = NO_ACTION};

    return Event{.type = NO_ACTION};
}

Event SidePanel::action(Event e){

    return Event{.type = NO_ACTION};
}


Panel::Panel(){

    _selected = false;

    _x=_y=_width=_height=5;
    _win = newwin(_height,_width,0,0);

    _dom = nullptr;
}

Panel::Panel(int x, int y, int w, int h){

    _selected = false;

    _x = x;
    _y = y;
    _width = w;
    _height = h;

    _win = newwin(h,w,y,x);

    _dom = nullptr;
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

    wclear(_win);
    Element * s = nullptr;
    Element * c = nullptr;

    int xOff = 1;
    int yOff = 1;

    if (_dom){
        _dom->rewind();
        s = _dom->getSelected();
        c = _dom->getHead();
    }
        
     while(_dom && !_dom->isEnd()){
        
        if (s == c){
            colorOn(_win, COLOR_CYAN, COLOR_WHITE);
            mvwprintw(_win, yOff, xOff, "%s", c->value.c_str());
            colorOff(_win, COLOR_CYAN, COLOR_WHITE);
            wrefresh(_win);
        } else {
            mvwprintw(_win , yOff, xOff, "%s", c->value.c_str());
        }

        //update x,y offsets based on relation to previous
        Element * n = _dom->next();

        if (n == c->up){
            ++yOff;
            xOff = 1;
        } else {
            xOff += c->value.size() + 1;
        }

        c = n;
    }

    _paintBorder();
    wrefresh(_win);
    refresh();
}

void Panel::setSelect(bool selected){

    _selected = selected;

    _clearBorder();
    _paintBorder();
}

void Panel::arrowDOMTarget(int dir){
    if (!_dom)
        return;
    
    _dom->select(dir);
    paint();
}

Event Panel::action(Event e){

    switch(e.val){
        case KEY_UP: arrowDOMTarget(SEL_UP); break;
        case KEY_DOWN: arrowDOMTarget(SEL_DOWN); break;
        case KEY_LEFT: arrowDOMTarget(SEL_LEFT); break;
        case KEY_RIGHT: arrowDOMTarget(SEL_RIGHT); break;
            
        break;
    }

    return Event {.type = NO_ACTION};
}

void Panel::renderDOM(){

}

void Panel::setDOM(DOM * dom){
    if (dom == nullptr)
        return;
    _dom = dom;
}

DOM * Panel::_getDOM(){
    return _dom;
}



Console::Console(){

    const int DEF_DIM = 5;

    _panels[WIN_MAIN] = new ContentPanel(0,0,DEF_DIM,DEF_DIM);
    _panels[WIN_TOOL] = new ToolPanel(0,0,DEF_DIM,DEF_DIM);
    _panels[WIN_SIDE] = new SidePanel(0,0,DEF_DIM,DEF_DIM);
    _panels[WIN_STAT] = new StatusPanel(0,0,DEF_DIM,DEF_DIM);

    resize();

    _panels[WIN_MAIN]->setDOM(updateContentDom(NULL));
    _panels[WIN_TOOL]->setDOM(initToolDom());

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
    
    _panels[_selected]->setSelect(false);
    _panels[select]->setSelect(true);
    _selected = select;
    _panels[select]->paint();
    refresh();
}

void Console::resize(){
    WinInfo wi = getTermDim();

    const int BAR_HEIGHT = 4;
    const int SB_WIDTH = 10;
    
    _panels[WIN_SIDE]->resize(SB_WIDTH, wi.h);
    _panels[WIN_SIDE]->moveTo(0, 0);

    _panels[WIN_TOOL]->resize(wi.w - SB_WIDTH, BAR_HEIGHT);
    _panels[WIN_TOOL]->moveTo(SB_WIDTH, 0);

    _panels[WIN_STAT]->resize(wi.w - SB_WIDTH, BAR_HEIGHT);
    _panels[WIN_STAT]->moveTo(SB_WIDTH, wi.h-BAR_HEIGHT);

    _panels[WIN_MAIN]->resize(wi.w - SB_WIDTH, wi.h - (2*BAR_HEIGHT));
    _panels[WIN_MAIN]->moveTo(SB_WIDTH, BAR_HEIGHT);
}

void Console::render(){
    for (int i = 0; i < 4; ++i){
        _panels[i]->clear();
        _panels[i]->paint();
    }
        
}

void Console::clearAll(){

}

void Console::clearPanel(int p){
    if (p<0 || p>=4)
        return;
    _panels[p]->clear();
}

void Console::focusNext(){

    _panels[_selected]->setSelect(false);

    if (_selected == WIN_STAT){
        _selected = WIN_MAIN;
    } else {
        ++_selected;
    }

    _panels[_selected]->setSelect(true);
}

void Console::focusPrev(){
    _panels[_selected]->setSelect(false);

    if (_selected == WIN_MAIN){
        _selected = WIN_STAT;
    } else {
        --_selected;
    }

    _panels[_selected]->setSelect(true);
}

void Console::wrenderDOM(int win){
    if (win < 0 || win > WIN_STAT)
        return;
    
    _panels[win]->renderDOM();
}

void Console::wsetDOM(int win, DOM * dom){
    if (win < 0 || win > WIN_STAT)
        return;
    
    _panels[win]->setDOM(dom);
}

void Console::action(Event e){

    Event r {.type = NO_ACTION};

    switch(e.val){

        case 9://TAB
            focusNext();
        break;
        case KEY_RESIZE:
            resize();
        break;

        default:
            {
                Panel * p = _panels[_selected];
                p->action(e);
            }
            //r = _panels[_selected]->action(e);
    }

    if (r.type == NO_ACTION)
        return;

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
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    refresh();

    //setup colors
    for (int i=COLOR_BLACK; i <= COLOR_WHITE; ++i){
        for (int j=COLOR_BLACK; j <= COLOR_WHITE; ++j){
            int pair = COLOR(i, j);
            init_pair(pair, i, j);
            
            attron(COLOR_PAIR(3));
            //colorOn();
            mvprintw(i,0, "TEST");
            //colorOff(i, j);
            attron(COLOR_PAIR(3));
        }
    }

    refresh();
    _terminal = new Console();

}

void Console::updateContent(){
    updateContentDom(_panels[WIN_MAIN]->_getDOM());
}

Console * getTerminal(){
    return _terminal;
}

void colorOn(WINDOW * w, int fg, int bg){
    wattron(w, COLOR_PAIR(COLOR(fg, bg)));
}

void colorOff(WINDOW * w, int fg, int bg){
    wattroff(w, COLOR_PAIR(COLOR(fg, bg)));
}


//DOM initializers
DOM * initToolDom(){
    DOM * d = new DOM();

    Element * locBar = new Element();
    Element * bExit = new Element();
    Element * bHome = new Element();

    locBar->type = E_TEXT;
    locBar->value = _bi.getPathURI();

    bExit->type = E_OPTION;
    bExit->value = "EXIT";
    bExit->action = [](void){
        _state.active=false;
        return int(1);
    };

    bHome->type = E_OPTION;
    bHome->value = "HOME";
    bHome->action = [](void){
        _bi.setURI("C://");
        _terminal->updateContent();
        return int(1);
    };

    d->addChild(locBar);

    d->addChild(bExit);
    d->addSibling(bHome);

    d->rewind();

    return d;
}

DOM * updateContentDom(DOM * cd){

    if (cd == nullptr)
        cd = new DOM();
    else
        cd->clear();
    
    vector <Path> paths = _bi.getDirList();

    for (Path p: paths){
        Element * e = new Element();
        e->value = p.toString();
        e->type = E_TEXT;

        if (p.target.size() > 0)
            e->value += "/" + p.target;

        cd->addChild(e);
    }

    cd->rewind();

    return cd;
}