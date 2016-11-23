#include "cIniStorage.h"

#include <iostream>

using namespace std;

void cIniStorage::load() {
    cIni* ini = new cIni("ini.ini");
    ini->load();

    container = ini->getContainer();
    
    for (size_t i = 0; i < container["lists"]["users"].size(); ++i) {
        addUser(cUser(container["lists"]["users"][i].data()));
    }
    for (size_t i = 0; i < container["lists"]["books"].size(); ++i) {
        addBook(cBook(container["lists"]["books"][i].data()));
    }

    delete ini;
    ini = nullptr;
}

