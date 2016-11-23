#ifndef _C_USER_H_
#define _C_USER_H_

class cUser {
public:
    cUser() :
        _id{ _last_id++ },
        _name{ _default_name } {}
    cUser(char* name);
    cUser(const char* name);
    ~cUser();
    char* getName() const;
    void setName(char* name);
    void setdefaultName(char* default_name);
    void setStartId(int start_id);
    bool operator==(cUser& rhs);
private:
    static int _last_id;
    //cUser(const cUser& rhs);//noncopyable
    static char* _default_name;
    int _id;
    char* _name;
};

#endif
