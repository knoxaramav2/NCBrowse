#include "console.h"

//using namespace CONSOLE;

//Console * _terminal;

Console::Console(){
    
}

Console::~Console(){

}


Key Console::getKey(){
    int i = getch();
    KeyType kt = KeyType::ascii;

    return Key{.key = i, .type = kt};
}

Console * getTerminal(){
    return _terminal;
}