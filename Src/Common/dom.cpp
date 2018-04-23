#include "dom.h"

using namespace std;

//recursively destroy tree
void killChild(Element * c){
    if (c == nullptr)
        return;
    
    killChild(c->up);
    killChild(c->right);

    delete c;
}


Element::Element(){
    right = left = up = down = nullptr;
    type = E_TEXT;

    action = [](void){return int(0);};
}

void Element::addChild(Element * e){
    this->up = e;
    e->down = this;
}

void Element::addSibling(Element * e){
    this->right = e;
    e->left = this;
}

DOM::DOM(){
    _itr = nullptr;
    _head = nullptr;
    _selected = nullptr;

    _end = true;
}

DOM::~DOM(){
    clear();
}

void DOM::clear(){
    killChild(_head);
    _selected = NULL;
    _itr = NULL;
    _end = true;
}

void DOM::rewind(){
    _itr = _head;
    _end = (_head == nullptr);
}

bool DOM::isEnd(){
    return _end;
}

void DOM::trigger(){
    if (!_itr)
        return;
}


Element * DOM::getCurrent(){
    return _itr;
}

Element * DOM::getHead(){
    return _head;
}

Element * DOM::addChild(Element * e){
    
    if (_head == nullptr){
        _head = _itr = e;
        _selected = _head;
    } else {
        _itr->addChild(e);
        _itr = e;
    }

    _end = false;

    return _itr;
}

Element * DOM::addSibling(Element * e){
    
    if (_head == nullptr){
        _head = _itr = e;
        _selected = _head;
    } else {
        _itr->addSibling(e);
        _itr = e;
    }

    _end = false;

    return _itr;
}

Element * DOM::next(){
    if (_itr == nullptr)
        return NULL;

    if (_itr->up)
        _itr = _itr->up;
    else if (_itr->right)
        _itr = _itr->right;
    else {
        while (_itr->down){
            _itr = _itr->down;

            if (_itr->right){
                _itr = _itr->right;
                return _itr;
            }
        }

        //NOTE: next() may be able to progress at this point
        _end = true;
    }

    return _itr;
}

Element * DOM::prev(){
    if (_itr == nullptr)
        return NULL;

    if (_itr->left)
        _itr = _itr->left;
    else if (_itr->down)
        _itr = _itr->down;

    return _itr;
}

Element * DOM::select(int dir){
    if (_selected == nullptr)
        return NULL;
    
    Element * e = NULL;

    switch(dir){
        case SEL_UP: e = _selected->down; break;
        case SEL_DOWN: e = _selected->up; break;
        case SEL_LEFT: e = _selected->left; break;
        case SEL_RIGHT: e = _selected->right; break;
    }

    if (e){
        _selected = e;
    }

    return _selected;
}

Element * DOM::getSelected(){
    return _selected;
}