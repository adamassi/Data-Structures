#ifndef WET1_DS_user
#define WET1_DS_user


class Group;

class User{
public:  
    int userId;
    bool isVip;
    Group* group;
    int total_watch;
    int comedy;
    int drama;
    int action;
    int fantasy;
    
public:
    User(int userId,bool isVip);
    ~User()=default;
    User():userId(-1),isVip(false),group(nullptr),total_watch(0),comedy(0),drama(0),action(0),fantasy(0){}
    User(int userId):userId(userId),isVip(false){}
    User(const User&)=default;
    bool isUserVIP();
};

class CompUsersByID {
public:
    bool operator()(User* p1, User* p2) const {
        return p1->userId < p2->userId;
    }
};
class EqualUsers {
public:
    bool operator()(User* p1, User* p2) const {
        if(p1 && p2)
            return p1->userId == p2->userId;
        return false;
    }
};

#endif
