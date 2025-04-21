#include "UnionFind.h"
#include <iostream>

recordsNode *UnionFind::findrecordsNode(int Record_index,int *to_return_h,int* to_return_col) {
    recordsNode *currRecord = recordss_array->array[Record_index]; //  I think without -1 - check  !!!!!!!
    if (currRecord == nullptr) {
        return nullptr;
    }
    
    int extra_val = 0;
    recordsNode *p = currRecord;
    while (currRecord->root != nullptr) {
        extra_val += currRecord->extra_h; // sum of extra_h from curr to root (not included)
        // currRecord->extra_h=currRecord->extra_h+extra_val;
        currRecord = currRecord->root;
    }
    

 //   int t_id=currRecord->r_id;
    recordsNode *father = currRecord;
    currRecord = p;
    recordsNode *temp = p->root;
    int temp_val = 0;
    int sum_prev=0;
   if(temp!=nullptr){
       while (temp->root) {
         sum_prev=currRecord->extra_h;

            // currRecord->extra_h =sum_prev;

            currRecord->extra_h = (extra_val - temp_val);
            temp_val+=sum_prev;

           currRecord->root = father;
        //    currRecord->r_id=t_id;
            currRecord = temp;
            temp = currRecord->root;
            
       }
   }
    *to_return_col=father->column;
    if(p->index==father->index){
    *to_return_h=father->extra_h;
    return father;
    }
    *to_return_h=p->extra_h+father->extra_h;
    return father;
}

recordsNode* UnionFind::find(int Record_index,int *to_return_h,int* to_return_col) {
     if (findrecordsNode(Record_index,to_return_h,to_return_col) == nullptr)
         return nullptr;
     return findrecordsNode(Record_index,to_return_h,to_return_col);
}


void UnionFind::Union(int index1, int index2) {
    int to_return_h,to_return_col;
    recordsNode* first_record=find(index1,&to_return_h,&to_return_col);
     int size1 = first_record->size;
     recordsNode* root1=findrecordsNode(index1,&to_return_h,&to_return_col);
     // get bought
    recordsNode* bought_team=find(index2,&to_return_h,&to_return_col);
      int size2 = bought_team->size;
     recordsNode* root2=findrecordsNode(index2,&to_return_h,&to_return_col);
     if(root1->r_id==root2->r_id)
         return;


     if(size1 < size2){
        root2->column=root2->min_column;
        // if (root1->min_column<root2->min_column)
        // {
        //     root2->min_column=root1->min_column;
        // }
        
         root2->size+=root1->size;
         //root1->extra_h-=root2->extra_h;

         root2->height=root1->extra_h+root2->height+root1->height;
         root1->extra_h=(root2->height)-root1->height;
        

         //root1->extra_h=(root1->extra_h)+(root2->height)-(root2->extra_h);
         root1->root=root2;
        //  root1->column=root2->column;
        
         
     }
     else{
        // if(root1->min_column>root2->min_column){
        //     root1->min_column=root2->min_column;
        // }
         root1->min_column=root2->min_column;
         root1->size+=root2->size;
         root1->extra_h=root1->extra_h+root2->height+root2->extra_h;
         root2->extra_h=root2->extra_h-root1->extra_h;
         root1->column=root2->min_column;
         root2->root=root1;
     }
}

    