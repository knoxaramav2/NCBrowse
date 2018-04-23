#ifndef CM_DOM
#define CM_DOM

#include <string>
#include <vector>
#include <functional>

#define SEL_UP      0
#define SEL_DOWN    1
#define SEL_RIGHT   2
#define SEL_LEFT    3

enum ElementType{
    E_TEXT,     //non interactable
    E_LINK,     //references another location or activates element
    E_OPTION    //Performs special action
};

class Element{

    public:

    Element();

    Element * right;
    Element * left;
    Element * up;
    Element * down;

    ElementType type;

    //printable value
    std::string value;
    //content data
    std::string info;

    void addChild(Element *);
    void addSibling(Element *);

    std::function<int(void)> action;
};

class DOM{

    Element * _itr;
    Element * _head;
    Element * _selected;

    bool _end;

    public:

    DOM();
    ~DOM();

    Element * getCurrent();
    Element * getHead();

    Element * addChild(Element *);
    Element * addSibling(Element *);

    Element * next();
    Element * prev();

    Element * select(int);
    Element * getSelected();

    void rewind();
    void clear();

    bool isEnd();

    void trigger();

};

#endif