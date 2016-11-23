#ifndef _C_BOOK_H_
#define _C_BOOK_H_


class cBook {
public:
    cBook() :
        _id{ _last_id++ },
        _name{ _default_name } {}
    
    cBook(char* name):
        _id{ _last_id++ },
        _name{ name }{}
    
    cBook(const char* name) :
        _id{ _last_id++ },
        _name{ (char*)name }
    {}
    
    ~cBook();
    char* getName() const;
    void setName(char* name);
    void setDefaultName(char* default_name);
    void setStartId(unsigned int start_id);

    bool operator==(cBook& rhs);
private:
    //cBook(const cBook& rhs);//noncopyable
    static unsigned int _last_id;
    static char* _default_name;
    unsigned int _id;
    char* _name;
};

#endif