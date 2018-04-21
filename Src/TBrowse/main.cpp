#include <string>
#include <iostream>

#include "modules.h"

#include "ncurses.h"

#include "graphics.h"

using namespace std;

void testDirs(){
    vector <string> test = splitBy("Test string/and/stuff/wasda", '/');

    for (string s : test){
        cout << s << endl;
    }

    vector <Path> ptest = getDirList("C:\\Users\\MMI\\Documents");

    for (Path s : ptest){
        cout << s.toString() << endl;
    }
}



int main(int argc, char *argv[])
{	
    
	initTerminal();

	Key k;
	Console * cs = getTerminal();

	//WINDOW * w = newwin(5, 5, 0, 0);
	//box(w, '*', '*');
	//wrefresh(w);

	int input = 0;

	//while ((k=Console::getKey()).key != KEY_F(1)){
	while ((input = getch()) != KEY_F(1)){

		switch (input){
			case 9://TAB
				cs->focusNext();
			break;
			default:

			break;
		}
	}

	clear();
	refresh();
	endwin();

	return 0;
}