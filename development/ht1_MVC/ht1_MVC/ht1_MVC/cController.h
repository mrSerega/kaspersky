#include "cModel.h"

#ifndef _C_CONTROLLER_H_
#define _C_CONTROLLER_H_

class cController {
public:
    cController();
    cController(cModel* model /*,cAbstractView* view*/);
    ~cController();

    void addUser(char* name);
    void addBook(char* name);

    int addBookToUser(cBook& book, cUser& user, unsigned int current_time);//TODO: проверка, на то можно ли добавить книгу
    int getBookFromUser(cBook& book, cUser& user);

    void getBooksOfUser(std::vector<cBook>& books, cUser& user);
    void getAllBooks(std::vector<cBook>& books);
    void getFreeBooks(std::vector<cBook>& books);
    void getAllUsers(std::vector<cUser>& users);
    void getBadUsers(std::vector<std::pair<cUser, cBook> >& users, unsigned int current_time);
private:
    static const unsigned int _max_num_of_books = 3;//TODO: сделать возможнсоть изменять
    static const unsigned int _max_time = 30;
    cModel* _model;
    //cAbstractView* _view;
};

#endif
