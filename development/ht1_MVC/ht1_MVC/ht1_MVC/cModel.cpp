#include "cModel.h"

cModel::cModel() {
    //TODO
}

cModel::cModel(std::vector<cBook> books, std::vector<cUser> users):
    _books{books},
    _users{users}{}

cModel::~cModel() {
    //pass
}

void cModel::addUser(cUser& user) {
    _users.push_back(user);
    _un.push_back(std::make_pair(user, 0));
}

void cModel::addBook(cBook& book) {
    _books.push_back(book);
    _bf.push_back(std::make_pair(book, true));
}

void cModel::addBookToUser(cBook& book, cUser& user, unsigned int time) {
    _ubt.push_back(std::make_pair(std::make_pair(user, book), time));
}

unsigned int cModel::getNumOfBookOfUser(cUser& user) {
    for (size_t i = 0;i < _un.size();++i) {
        if (_un[i].first == user) {
            return _un[i].second;
        }
    }
    throw std::exception("no user in list");
}

bool cModel::isItBookFree(cBook& book) {
    for (size_t i = 0;i < _bf.size();i++) {
        if (_bf[i].first == book) {
            return _bf[i].second;
        }
    }
    throw std::exception("no book in list");
}

int cModel::isUserHasBook(cUser& user, cBook& book) {
    for (size_t i = 0;i < _ubt.size();++i) {
        if ((_ubt[i].first.first == user) && (_ubt[i].first.second == book)) {
            return i;
        }
    }
    return -1;
}

void cModel::removeUBT(unsigned int pos) {
    _ubt.erase(_ubt.begin() + pos);
}

std::vector<cBook> cModel::getAllBooks() {
    return _books;
}

std::vector<cUser> cModel::getAllUsers() {
    return _users;
}

void cModel::setBookAsLock(cBook& book) {
    for (size_t i = 0;i < _bf.size();++i) {
        if (_bf[i].first == book) {
            _bf[i].second = false;
            return;
        }
    }
    throw std::exception("no book in list");
}

void cModel::setBookAsFree(cBook& book) {
    for (size_t i = 0;i < _bf.size();++i) {
        if (_bf[i].first == book) {
            _bf[i].second = true;
            return;
        }
    }
    throw std::exception("no book in list");
}

std::vector<std::pair<std::pair<cUser, cBook>, unsigned int> > cModel::getUBT() {
    return _ubt;
}

void cModel::setUsersNumOfBook(cUser& user, int num) {
    for (size_t i = 0;i < _un.size();i++) {
        if (_un[i].first == user) {
            _un[i].second = num;
        }
    }
}
