#include <sstream>
#include <iterator>

#include "util.h"

using namespace std;

vector<string> splitBy(string raw, char del){
    vector<string> ret;

    stringstream ss(raw);
    string tmp;
    while(getline(ss, tmp, del)){
        ret.push_back(tmp);
    }

    return ret;
}