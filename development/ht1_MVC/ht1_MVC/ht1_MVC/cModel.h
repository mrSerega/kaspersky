#include <vector>

#include "cBook.h"
#include "cUser.h"

#ifndef _C_MODEL_H_
#define _C_MODEL_H_

class cModel {
public:
    cModel();
    cModel(std::vector<cBook> books, std::vector<cUser> users);
    ~cModel();

    void addUser(cUser& user);
    void addBook(cBook& book);

    void addBookToUser(cBook& book, cUser& user, unsigned int time);

    unsigned int getNumOfBookOfUser(cUser& user);
    bool isItBookFree(cBook& book);
    int isUserHasBook(cUser& user, cBook& book);

    void removeUBT(unsigned int pos);

    void setBookAsLock(cBook& book);
    void setBookAsFree(cBook& book);

    void setUsersNumOfBook(cUser& user, int num);

    std::vector<cBook> getAllBooks();
    std::vector<cUser> getAllUsers();

    std::vector<std::pair<std::pair<cUser, cBook>, unsigned int> > getUBT();
    virtual void load() = 0;
private:
    std::vector<cBook> _books;
    std::vector<cUser> _users;
    std::vector<std::pair<std::pair<cUser, cBook>, unsigned int> > _ubt;//user, book, time
    std::vector<std::pair<cUser, unsigned int> > _un;//user, num of books
    std::vector<std::pair<cBook, bool>> _bf;//book, is it free
};

#endif