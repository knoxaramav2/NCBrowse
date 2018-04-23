#include <string>
#include <iostream>

#include "modules.h"
#include "event.h"
#include "browseinfo.h"
#include "state.h"

#include "ncurses.h"

#include "graphics.h"

using namespace std;

void testDirs(){

    vector <Path> ptest = getDirList("");

    for (Path s : ptest){
        cout << s.toString() << endl;
    }
}

int main(int argc, char *argv[])
{	
	_bi.setURI(argv[0]);
	initTerminal();

	FDOM fd(argv[0]);
	Console * cs = getTerminal();

	int input = 0;

	//while ((k=Console::getKey()).key != KEY_F(1)){
	while (((input = getch()) != KEY_F(1)) && _state.active){
		Event e{
			.type = KEY_STROKE,
			.val = input
		};

		cs->action(e);
	}

	clear();
	refresh();
	endwin();

	return 0;
}