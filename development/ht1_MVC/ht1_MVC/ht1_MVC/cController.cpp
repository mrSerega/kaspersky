#include "cUser.h"
#include "cBook.h"

#include "cController.h"

cController::cController() {
    //TODO
}

cController::cController(cModel* model/*, cAbstractView* view*/) :
    _model{ model } {}
    //_view{view}{}

cController::~cController() {
    //pass
}

void cController::addUser(char* name) {
    _model->addUser(cUser(name));
}

void cController::addBook(char* name) {
    _model->addBook(cBook(name));
}

int cController::addBookToUser(cBook& book, cUser& user,unsigned int current_time) {
    if (_model->getNumOfBookOfUser(user) < _max_num_of_books) {
        if (_model->isItBookFree(book)) {
            _model->addBookToUser(book, user, current_time);
            _model->setBookAsLock(book);
            _model->setUsersNumOfBook(user, _model->getNumOfBookOfUser(user) + 1);
            return 0;
        }
        return -1;//book is not free
    }
    return -1;//user have more books then possible
}

int cController::getBookFromUser(cBook& book, cUser& user) {
    int pos = _model->isUserHasBook(user, book);
    if (pos!=-1) {
        _model->removeUBT(pos);
        _model->setBookAsFree(book);
        _model->setUsersNumOfBook(user, _model->getNumOfBookOfUser(user) - 1);
        return 0;
    }
    return -1;
}

void cController::getAllBooks(std::vector<cBook>& books) {
    books = _model->getAllBooks();
}

void cController::getFreeBooks(std::vector<cBook>& books) {
    std::vector<cBook> tmp = _model->getAllBooks();
    books.clear();
    for (size_t i = 0;i < tmp.size();i++) {
        if (_model->isItBookFree(tmp[i])) {
            books.push_back(tmp[i]);
        }
    }
}

void cController::getAllUsers(std::vector<cUser>& users) {
    users = _model->getAllUsers();
}

void cController::getBadUsers(std::vector<std::pair<cUser, cBook> >& users, unsigned int current_time) {
    users.clear();
    std::vector<std::pair<std::pair<cUser, cBook>, unsigned int> > tmp = _model->getUBT();
    for (size_t i = 0;i < tmp.size();++i) {
        if (current_time - tmp[i].second > _max_time) {
            users.push_back(tmp[i].first);
        }
    }
}

void cController::getBooksOfUser(std::vector<cBook>& books, cUser& user) {
    std::vector<std::pair<std::pair<cUser, cBook>, unsigned int> > tmp = _model->getUBT();
    books.clear();
    for (size_t i = 0;i < tmp.size();i++) {
        if (tmp[i].first.first == user) {
            books.push_back(tmp[i].first.second);
        }
    }
}