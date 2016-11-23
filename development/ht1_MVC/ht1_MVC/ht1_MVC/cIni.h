#include <map>
#include <vector>

#include <fstream>
#include <string>

#ifndef C_INI_H
#define C_INI_H

#define COMMENT '#'
#define VAR_SPLIT '='
#define ARR_SPLIT ','
#define SEC_START '['
#define SCE_END ']'

class cIni
{
public:
    cIni(char* ini_name);
    void load();
    //void update();
    std::map < std::string, std::map<std::string, std::vector < std::string> > > getContainer();
private:
    char* _ini_name;
    std::ifstream in;
    std::ofstream out;
    std::map < std::string, std::map<std::string,std::vector < std::string> > > container;
    std::vector<std::string> split(std::string line, char simbol);
};

#endif