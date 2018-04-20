#ifndef FBROWSE
#define FBROWSE

#include <string>
#include <vector>

struct Path{
    std::vector<std::string> path;
    std::string target;
    bool isFolder;

    Path();
    Path(std::string);
    Path(std::string, std::string);

    std::string toString();
};

class Directory{

    Path _currDirectory;

    public:

    std::string getCurrentDir();
    std::vector <Path> getCurrDirList();

};

std::vector <Path> getDirList(std::string);

#endif