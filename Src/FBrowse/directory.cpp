#include <stdio.h>
#include <cstring>
#include <dirent.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fbrowse.h"
#include "util.h"

using namespace std;

bool isFile(string path){
    struct stat s;
    if (stat(path.c_str(), &s) == 0){
        if (s.st_mode & S_IFDIR) return false;
        return (s.st_mode & S_IFREG);
    }

    return false;
}

string normalizePath(string raw){
    replace(raw.begin(), raw.end(), '\\', '/');
    return raw;
}

Path::Path(){
    isFolder = true;
}

Path::Path(string _path){
    _path = normalizePath(_path);
    isFolder = !isFile(_path);
    path = splitBy(_path, '/');

    if (path.size() == 0)
        return;

    if (!isFolder){
        target = path[path.size()-1];
        path.pop_back();
    }
}

Path::Path(string _path, string _target){
    _path = normalizePath(_path);
    isFolder = !isFile(_path);
    path = splitBy(_path, '/');
    target = _target;
}


string Path::toString(){
    string ret;

    for (string str : path){
        ret += str + '/';
    }

    ret += target;

    return ret;
}

string Directory::getCurrentDir(){
    return _currDirectory.toString();
}

vector <Path> Directory::getCurrDirList(){
    return getDirList(_currDirectory.toString());
}

vector <Path> getDirList(string path){
    path = normalizePath(path);
    vector <Path> ret;
    DIR * dir;
    struct dirent * ent;

    if ((dir = opendir(path.c_str())) == NULL){
        return ret;
    }

    while((ent = readdir(dir))){
        ret.push_back(Path(path + "/" + ent->d_name));
    }

    closedir(dir);

    return ret;
}

