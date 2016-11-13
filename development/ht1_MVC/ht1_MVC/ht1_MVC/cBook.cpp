#include <exception>

#include "cBook.h"

unsigned int cBook::_last_id = 0;
char* cBook::_default_name = "default";

//cBook::cBook(const cBook& rhs) {
//    throw std::exception("noncopyable object");
//}

cBook::~cBook() {
    //pass
}

char* cBook::getName() const {
    return _name;
}

void cBook::setName(char* name) {
    _name = name;
}

void cBook::setDefaultName(char* default_name) {
    _default_name = default_name;
}

void cBook::setStartId(unsigned int start_id) {
    _last_id = start_id;
}

bool cBook::operator==(cBook& rhs) {
    if (_id == rhs._id) return true;
    return false;
}