#include "cIni.h"

using namespace std;

cIni::cIni(char* ini_name) :
    _ini_name{ ini_name }
{}

void cIni::load() {
    in.open(_ini_name);
    string str;
    int tmp;
    string section_name;
    string variable;
    string _value;
    vector<string> value;

    while ((tmp = in.get()) != EOF) {
        char tmp_char = static_cast<char>(tmp);
        string push = "";
        push += tmp_char;
        getline(in, str);
        push += str;

        if (push[0] == COMMENT) continue;

        if (push[0] == SEC_START) {
            section_name = push.substr(1, push.size() - 2);
            continue;
        }

        int found;
        found = push.find_first_of(VAR_SPLIT);
        variable = push.substr(0, found);
        _value = push.substr(found + 1, push.size() - 1);
        value = split(_value, ARR_SPLIT);

        container[section_name][variable] = value;
    }

    in.close();
}

vector<string> cIni::split(string line, char simbol) {
    vector<string> res;
    int found = 0;
    while (found != string::npos) {
        found = line.find_first_of(simbol);
        res.push_back(line.substr(0, found));
        if (found == string::npos) break;
        line.erase(line.begin(), line.begin()+found + 1);
    }
    return res;
}

map<string,map<string,vector<string> > > cIni::getContainer() {
    return container;
}