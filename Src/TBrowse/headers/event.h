#ifndef E_EVENT
#define E_EVENT

#include <string>

enum EType{
    NO_ACTION,
    KEY_STROKE,
    LOAD_RESOURCE
};

struct Event{
    EType type;
    int val;
    std::string info;
};

class Actable{

    public:

    virtual Event action(Event) = 0;

};

#endif