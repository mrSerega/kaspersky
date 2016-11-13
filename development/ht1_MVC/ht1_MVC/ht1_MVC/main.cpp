#include "cView.h"

int main(int argc, char* argv[]) {
    unsigned int curent_time = 40;

    cModel* model = new cModel();

    model->addBook(cBook("book1"));
    model->addBook(cBook("book2"));
    model->addBook(cBook("book3"));
    model->addBook(cBook("book4"));
    model->addBook(cBook("book5"));
    model->addBook(cBook("book6"));
    model->addBook(cBook("book7"));
    model->addBook(cBook("book8"));
    model->addBook(cBook("book9"));
    model->addBook(cBook("book0"));

    model->addUser(cUser("user1"));
    model->addUser(cUser("user2"));
    model->addUser(cUser("user3"));
    model->addUser(cUser("user4"));
    model->addUser(cUser("user5"));
    model->addUser(cUser("user6"));
    model->addUser(cUser("user7"));
    model->addUser(cUser("user8"));
    model->addUser(cUser("user9"));
    model->addUser(cUser("user0"));

    cController* controller = new cController(model);
    cConsoleView* view = new cConsoleView(controller, model);
    
    view->start(curent_time);
    
    delete view;
    delete controller;
    delete model;
    return 0;
}