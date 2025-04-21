#include "user.h"

User::User(int userId,bool isVip )
        : userId(userId),isVip(isVip),group(nullptr),total_watch(0),comedy(0),drama(0),action(0),fantasy(0){}

bool User::isUserVIP() {
    return this->isVip;
}

