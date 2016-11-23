#include "cModel.h"


#include "cIni.h"


#ifndef C_INISTORAGE_H
#define C_INISTORAGE_H


class cIniStorage :
    public cModel
{
public:
    void load();
private:
    std::map<std::string, std::map<std::string, std::vector <std::string> > > container;
};

#endif