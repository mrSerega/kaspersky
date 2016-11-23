#include "cView.h"

#include "cIni.h"

#include "cLocalStorage.h"
#include "cIniStorage.h"
#include "cCloudStorage.h"

#include <iostream>

int main(int argc, char* argv[]) {
    unsigned int curent_time = 40;

    cModel* model;

    std::cout << "enter [1] to load data from local storage\n";
    std::cout << "enter [2] to load data from ini file\n";
    std::cout << "enter [3] to load data from cloud storage\n";
    
    int com;
    std::cin >> com;

    switch (com)
    {
    case 1:
        model = new cLocalStorage();
        break;
    case 2:
        model = new cIniStorage();
        break;
    case 3:
        model = new cCloudStorage();
        break;
    default:
        model = new cLocalStorage();
        break;
    }

    model->load();

    cController* controller = new cController(model);
    cConsoleView* view = new cConsoleView(controller,model);
    
    view->start(curent_time);
    
    delete view;
    delete controller;
    delete model;
    return 0;
}