#include <dlfcn.h>
#include <stdlib.h>
#include <iostream>

#include "common.h"

using namespace std;

static void startup() __attribute__((constructor));
static void shutdown() __attribute__((destructor));

void startup(){
    cout << "COMMON" << endl;
}

void shutdown(){
    
}

void cTest(){
    cout << "MEH" << endl;
}