#include <string>
#include <iostream>

//#include "modules.h"

#include "ncurses.h"

using namespace std;

int main(int argc, char ** argv){

    //Console c;

    initscr();
    mvprintw(0,0,"HELLO");
    refresh();
    endwin();

    return 0;
}