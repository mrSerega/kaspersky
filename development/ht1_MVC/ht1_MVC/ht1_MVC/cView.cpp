#include <iostream>

#include "cView.h"

#include "cLocalStorage.h"
#include "cCloudStorage.h"
#include "cIniStorage.h"

cAbstractView::~cAbstractView() {
    //pass
}

cConsoleView::cConsoleView(cController* controller, cModel* model) :
    cAbstractView(controller, model) {}

cAbstractView::cAbstractView(const cAbstractView& rhs) {
    //pass
}

using namespace std;

void cConsoleView::start(unsigned int curent_time){
    _curent_time = curent_time;
    //startScreen();
    int com = 1;
    while (com!=0) {
        printMenu();
        cin >> com;
        switch (com) {
        case 1:
            clearCMD();
            printAllBooks();
            pause();
            break;
        case 2:
            clearCMD();
            printFreeBooks();
            pause();
            break;
        case 3:
            clearCMD();
            printAllUsers();
            pause();
            break;
        case 4:
            clearCMD();
            printBadUsers();
            pause();
            break;
        case 5:
            clearCMD();
            addBookToUser();
            pause();
            break;
        case 6:
            clearCMD();
            getBookFromUser();
            pause();
            break;
        case 7:
            clearCMD();
            changeTime();
            pause();
            break;
        case 8:
            clearCMD();
            printUserBook();
            pause();
            break;
        default:
            //pass
            break;
        }
    }
}

void cConsoleView::startScreen() {
    cout << "===Welcome to the Lib===current time is: "<<_curent_time<<"(days from the date of opening)===\n";
    cout << "choose a source please:\n";
    cout << "[0] local storage\n";
    cout << "[1] ini file\n";
    cout << "[2] cloud storage\n";
    cout << ">> ";
    int com;
    cin >> com;
    switch (com)
    {
    case 0:
        delete _model;
        (*_model) = (*new cLocalStorage());
        _model->load();
        break;
    case 1:
        delete _model;
        (*_model) = (*new cIniStorage());
        _model->load();
        break;
    case 2:
        delete _model;
        (*_model) = (*new cCloudStorage());
        _model->load();
        break;
    default:
        cout << "wrong command!\n";
        pause();
        clearCMD();
        startScreen();
        break;
    }
}

void cConsoleView::printMenu()  {
    //pause();
    clearCMD();
    cout << "====menu====time:"<<_curent_time<<endl;
    cout << "[1] print all books\n";
    cout << "[2] print free books\n";
    cout << "[3] print all users\n";
    cout << "[4] print bad users\n";
    cout << "[5] add book to user\n";
    cout << "[6] get book from user\n";
    cout << "[7] change time\n";
    cout << "[8] print users and books\n";
    cout << "[0] exit\n";
    cout << "---------------\n";
    cout << "enter a com: ";
}

void cConsoleView::clearCMD()  {
    system("cls");
}

void cConsoleView::printAllBooks(){
    //clearCMD();
    cout << "====list of books====\n";
    _controller->getAllBooks(books);
    for (size_t i = 0;i < books.size();i++) {
        cout <<i<<":"<< books[i].getName() << endl;
    }
}

void cConsoleView::printFreeBooks() {
    //clearCMD();
    cout << "====list of free books====\n";
    _controller->getFreeBooks(books);
    for (size_t i = 0;i < books.size(); ++i) {
        cout <<i<<":"<<  books[i].getName() << endl;
    }
    //pause();
}

void cConsoleView::printAllUsers()  {
    //clearCMD();
    cout << "====list of users====\n";
    _controller->getAllUsers(users);
    for (size_t i = 0;i < users.size(); ++i) {
        cout <<i<<":"<< users[i].getName() << endl;
    }
    //pause();
}

void cConsoleView::printBadUsers() {
    clearCMD();
    cout << "====list of bad users====\n";
    vector<pair<cUser, cBook> > vec;
    _controller->getBadUsers(vec, _curent_time);
    for (size_t i = 0;i < vec.size();++i) {
        cout << vec[i].first.getName() << "\t" << vec[i].second.getName() << endl;
    }
    //pause();
}

void cConsoleView::addBookToUser()  {
    int user_id, book_id, curent_time;
    clearCMD();
    cout << "====add book to user====\n";
    printAllUsers();
    cout << "enter id of user ";
    cin >> user_id;
    clearCMD();
    cout << "====add book to user====\n";
    printFreeBooks();
    cout << "enter if of book ";
    cin >> book_id;
    //cout << "enter time(num of day in year) ";
    //cin >> curent_time;
    int msg = _controller->addBookToUser(books[book_id], users[user_id], _curent_time);
    if (msg == -1) {
        clearCMD();
        cout << "=================\n";
        cout << "impossible action\n";
        cout << "=================\n";
    }
    //pause();
}

void cConsoleView::getBookFromUser() {
    clearCMD();
    cout << "====get book from user====\n";
    cout << "users:\n";
    printAllUsers();
    int user_id;
    cout << "enter user id ";
    cin >> user_id;
    clearCMD();
    cout << "====get book from user====\n";
    cout << "books:\n";
    printBooksOfUser(users[user_id]);
    int book_id;
    cout << "enter book id ";
    cin >> book_id;
    _controller->getBookFromUser(books[book_id], users[user_id]);
    //pause();
}

void cConsoleView::addUser() {
    cout << "coming soon\n";
    //pause();
}

void cConsoleView::addBook()  {
    cout << "coming soon\n";
    //pause();
}

void cConsoleView::pause() {
    system("pause");
    //pause();
}

void cConsoleView::changeTime() {
    cout << "enter time(day of year)";
    int curent_time;
    cin >> curent_time;
    _curent_time = curent_time;
}

void cConsoleView::printUserBook() {
    vector<pair<cUser, cBook> > vec;
    _controller->getBadUsers(vec, 0);
    for (size_t i = 0;i < vec.size();++i) {
        cout << vec[i].first.getName() << "\t" << vec[i].second.getName() << endl;
    }
}
void cConsoleView::printBooksOfUser(cUser& user) {
    _controller->getBooksOfUser(books, user);
    for (size_t i = 0;i < books.size();++i) {
        cout <<i<<":"<< books[i].getName() << endl;
    }
}