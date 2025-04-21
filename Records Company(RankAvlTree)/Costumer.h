//
// Created by admin on 6/6/2023.
//

#ifndef WET2_DS_spr_Costumer_H
#define WET2_DS_spr_Costumer_H

#include "GenericNode.h"
#include <stdlib.h>

#include "utilesWet2.h"

class Costumer
{
public:
int id ;
int phone;
bool member;
int expenses;
public:
    Costumer(int id ,int phone):id(id),phone(phone),member(false),expenses(0){};
    Costumer(int id):id(id),phone(-1),member(false),expenses(0){};
    ~Costumer()=default;
     int getid()const;
     Costumer& operator=(const Costumer&) = default; //=delete? 
    bool operator==(const Costumer &t) const;
    bool operator!=(const Costumer &t) const;
    bool operator<(const Costumer &t) const;
    bool operator>(const Costumer &t) const;
    bool operator<=(const Costumer &t) const;
    bool operator>=(const Costumer &t) const;




};
class CompCostumersByID {
public:
    bool operator()(Costumer *t1, Costumer *t2) const {
        return t1->id < t2->id;
    }
};
class EqualCostumers {
public:
    bool operator()(Costumer *t1, Costumer *t2) const {
        return t1->id == t2->id;
    }
};
// class CompCostumersByAbility{
//     public:
//     bool operator()(Costumer *t1, Costumer *t2) const {
//         if(t1->ability == t2->ability) return t1->getid() < t2->getid();
//         return t1->ability < t2->ability;
//     }
// };
// Costumer::Costumer(/* args */)
// {
// }

// Costumer::~Costumer()
// {
// }




#endif //WET2_DS_spr_Costumer_H
