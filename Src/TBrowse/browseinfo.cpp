#include "browseinfo.h"

using namespace std;

BrowseInfo _bi;

BrowseInfo::BrowseInfo(){

}

void BrowseInfo::setURI(std::string uri){
    _dir = Directory(uri);
}

string BrowseInfo::getPathURI(){
    return _dir.getCurrentDir();
}

Path BrowseInfo::getCurrPath(){
    return _dir.getCurrentDir();
}

vector<Path> BrowseInfo::getDirList(){
    return _dir.getCurrDirList();
}