#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include "graphics.h"

using namespace std;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup(){
    cout << "GRAPHICS" << endl;
}

void shutdown(){
    
}