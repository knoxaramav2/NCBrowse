#ifndef F_FDOM
#define F_FDOM

#include <string>

#include "dom.h"
#include "fbrowse.h"

class FDOM : public DOM{

    Directory _dir;

    public:

    FDOM(std::string);
    //~FDOM();

};

#endif