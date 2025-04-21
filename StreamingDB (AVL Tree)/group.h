#ifndef WET1_DS_group
#define WET1_DS_group
#include "AVLTree.h"
#include "user.h"
#include "wet1util.h"


class Group{
public:
    int groupId;
    int numVipUsers;
    AVLtree<User*,CompUsersByID,EqualUsers>* users_group;
    int comedy;
    int drama;
    int action;
    int fantasy;
    Genre max_genre;///lsho hda 
    int max_views;
public:
    Group(int groupId);
    Group()=default;
    ~Group(){
        delete users_group;
    }
    Genre get_max_genre();
    int get_genre_views(Genre genre);
    void update_max_in_group();
    Group& operator=(const Group&) = default;
};
class CompGroupsByID {
public:
    bool operator()(Group *t1, Group *t2) const {
        return t1->groupId < t2->groupId;
    }
};
class EqualGroup {
public:
    bool operator()(Group *t1, Group *t2) const {
        return t1->groupId == t2->groupId;
    }
};


#endif
