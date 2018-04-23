#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include "htmd.h"

using namespace std;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup(){
        //cout << "LOADED HTMD" << endl;
}

void shutdown(){
    
}