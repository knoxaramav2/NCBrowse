#ifndef B_BROWSE
#define B_BROWSE

#include <string>
#include <vector>

#include "fbrowse.h"

class BrowseInfo{

    Directory _dir;

    public:

    BrowseInfo();

    void setURI(std::string);
    std::string getPathURI();
    Path getCurrPath();
    std::vector <Path> getDirList();

};

extern BrowseInfo _bi;

#endif