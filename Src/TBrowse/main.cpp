#include <string>
#include <iostream>

#include "modules.h"

#include "ncurses.h"

using namespace std;

int main(int argc, char ** argv){

    vector <string> test = splitBy("Test string/and/stuff/wasda", '/');

    for (string s : test){
        cout << s << endl;
    }

    vector <Path> ptest = getDirList("C:\\Users\\MMI\\Documents");

    for (Path s : ptest){
        cout << s.toString() << endl;
    }

    return 0;
}