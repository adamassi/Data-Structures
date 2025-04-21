#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include <iostream>
#include "UnionFind.h"
#include "Costumer.h"
#include "RankAvlTree.h"
#include "HashTable.h"



class RecordsCompany {
  private:
    // todo
    int counter;//mshan al Uonion find
	RankAvlTree<Costumer *, CompCostumersByID, EqualCostumers> *club_members;
	 //HashTable<Record *> *records_hash_table;
	HashTable<Costumer*>* costumers_hash_table;
	UnionFind* uf;
  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
};

#endif