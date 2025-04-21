#include "group.h"

Group::Group(int groupId):groupId(groupId),numVipUsers(0),comedy(0),drama(0),action(0),fantasy(0)
        ,max_genre(Genre::COMEDY),max_views(0) {

    users_group=new  AVLtree<User*,CompUsersByID,EqualUsers>();
}




Genre Group::get_max_genre() {
    return this->max_genre;
}

int Group::get_genre_views(Genre genre) {
    if(genre==Genre::COMEDY) {
        return comedy;
    }
    else if(genre==Genre::DRAMA) {
        return drama;
    }
    else if(genre==Genre::ACTION) {
        return action;
    }
    else if(genre==Genre::FANTASY) {
        return fantasy;
    }
    return -1;
    //-1 tslekt 7al
    //ola mrh lazem ewsel han 
}

void Group::update_max_in_group() {
    if(comedy>drama && comedy >action && comedy >fantasy)
        max_genre=Genre::COMEDY;
    else if(drama>comedy && drama >action && drama>fantasy)
        max_genre=Genre::DRAMA;
    else if(action>comedy && action >drama && action>fantasy)
        max_genre=Genre::ACTION;
    else if(fantasy>comedy && fantasy >drama && fantasy>action)
        max_genre=Genre::FANTASY;
}
