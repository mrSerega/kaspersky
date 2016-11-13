#include <exception>

#include "cUser.h"

int cUser::_last_id = 0;
char* cUser::_default_name = "default";

//cUser::cUser(const cUser& rhs) {
//    throw std::exception("noncopyable object");
//}

cUser::~cUser() {
    //pass
}

char* cUser::getName() const {
    return _name;
}

void cUser::setName(char* name) {
    _name = name;
}

void cUser::setdefaultName(char* default_name) {
    _default_name = default_name;
}

void cUser::setStartId(int id) {
    _last_id = id;
}


bool cUser::operator==(cUser& rhs) {
    if (_id == rhs._id) return true;
    return false;
}