#include "cController.h"
#include "cModel.h"

#ifndef _C_VIEW_H_
#define _C_VIEW_H_
 
class cAbstractView {
public:
    cAbstractView() {};
    cAbstractView(cController* controller, cModel* model) :
        _controller{ controller },
        _model{ model } {};
    cAbstractView(const cAbstractView& rhs);
    ~cAbstractView();
    
    virtual void start(unsigned int curretn_time)  = 0;

    virtual void printAllBooks()  = 0;
    virtual void printFreeBooks()  = 0;
    virtual void printAllUsers()  = 0;
    virtual void printBadUsers() = 0;
    virtual void addBookToUser()  = 0;
    virtual void getBookFromUser()  = 0;
    virtual void addUser()  = 0;
    virtual void addBook()  = 0;
protected:
    std::vector<cUser> users;
    std::vector<cBook> books;
    cController* _controller;
    cModel* _model;
    unsigned int _curent_time;
};

class cConsoleView : public cAbstractView {
public:
    cConsoleView() : cAbstractView() {}
    cConsoleView(cController* controller, cModel* model);
    
    void start(unsigned int current_time)  ;
    
    void printMenu() ;
    void clearCMD() ;
    void pause();
 
    void printAllBooks() ;
    void printFreeBooks() ;
    void printAllUsers() ;
    void printBadUsers() ;
    void addBookToUser() ;
    void getBookFromUser() ;
    void addUser();
    void addBook() ;
    void changeTime();
    void printUserBook();
    void printBooksOfUser(cUser& user);
};

#endif
