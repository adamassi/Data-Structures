#ifndef UNIONFIND_H_
#define UNIONFIND_H_

#include "dynamicArr.h"
#include "exceptions.h"



class recordsNode {
public:
    int index;
    int num_records;
    int r_id;//hoe nfso m7lo balm3ra5 (index)
    int extra_h;/// for games aplayed
    int size;
    int purchases;
    recordsNode *root;
    int column,height;
    int min_column;

    recordsNode(int index,int num_records, int r_id,int extra_h ) : index(index), num_records(num_records),r_id(r_id), extra_h(extra_h), size(1),purchases(0), root(nullptr)
    ,column(r_id),height(num_records),min_column(r_id){}
    recordsNode() :index(-1), num_records(0),r_id(0), extra_h(0), size(1),purchases(0), root(nullptr),column(-1),height(-1),min_column(-1) {}
    ~recordsNode() {}
    recordsNode& operator=(recordsNode &other) {
        if (this == &other) {
            return *this;
        }
        this->index = other.index;
        this->num_records = other.num_records;
        this->r_id = other.r_id;
        this->size = other.size;
        this->extra_h = other.extra_h;
        this->root = other.root;
        this->column=other.column;
        this->height=other.height;
        this->min_column=other.min_column;
        return *this;
    }
};

/*===============================================================================================================*/
/*================================ Groups are teams, Members are recordss =========================================*/
/*===============================================================================================================*/


class UnionFind {
public:
    DynArray<recordsNode*> *recordss_array;
    
    UnionFind() : recordss_array(new DynArray<recordsNode*>()) {}

    void Union(int index1, int index2);


    recordsNode* MakeSet(int index, recordsNode* records_to_add){
        recordsNode* ptr;
        try
        {
            ptr = recordss_array->insert(records_to_add);
        }
        catch(const std::exception& e)
        {
            throw e;
        }
        return ptr;
    }
    void intitalz(){
        try
        {
             recordss_array->clear();
        }
        catch(const std::exception& e)
        {
            throw e;
        }
    }
    void remove(){
        try
        {
             recordss_array->remove_top();
        }
        catch(const std::exception& e)
        {
            throw e;
        }
    }

    recordsNode* findrecordsNode(int Record_indexint ,int *to_return_h,int* to_return_col);
    recordsNode* find(int Record_indexint ,int *to_return_h,int* to_return_col) ;

    ~UnionFind() {
        delete recordss_array;
    }
};


#endif