#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
{
    counter=0; 
	club_members=new RankAvlTree<Costumer *, CompCostumersByID, EqualCostumers>();
	//records_hash_table=new HashTable<Record *>();
	costumers_hash_table=new HashTable<Costumer*>(); 
	uf= new UnionFind();
}

RecordsCompany::~RecordsCompany()
{
     for (int i = 0; i < costumers_hash_table->size; i++)
    {
        Node<Costumer *> *curr = costumers_hash_table->table[i].getFirst();

            while (curr != nullptr) {
                Node<Costumer*> *temp = curr;
                curr = curr->next;
                delete temp->data;
            }
            delete curr;
    }
    for ( int i = 0; i <uf->recordss_array->filled; i++) {
            delete uf->recordss_array->array[i];
        }
        // int num_costumers = club_members->num_of_nodes;
        // Costumer **costumers_arr = new Costumer *[num_costumers];
        // club_members->storeInOrderToArray(costumers_arr);
        // for (int i = 0; i < num_costumers; i++) {
        //     delete costumers_arr[i];
        // }
    delete costumers_hash_table;
    //delete [] costumers_arr;
    delete club_members;
    delete uf;
}

StatusType RecordsCompany::newMonth(int * records_stocks, int number_of_records)
{
    // for ( int i = 0; i <uf->recordss_array->filled; i++) {

    //         delete uf->recordss_array->array[i];
    //     }
    //     uf->intitalz();
    club_members->InOrder_e_zeroe();
    int size=uf->recordss_array->filled;

    for ( int i = 0; i <size; i++) {

            uf->remove();
        }



        // recordsNode **new_array = new recordsNode*[INITIAL_SIZE];
        // delete[] uf->recordss_array->array;
        // uf->recordss_array->array=new_array;
    for (int i = 0; i < costumers_hash_table->size; i++)
    {
        Node<Costumer *> *curr = costumers_hash_table->table[i].getFirst();

            while (curr != nullptr) {
                
                curr->data->expenses=0;
                curr = curr->next;
                
            }
            
    }
    counter=0;
    for (int i = 0; i < number_of_records; i++)
    {
        recordsNode* r_add=new recordsNode(counter,records_stocks[i],counter,0);
        recordsNode* r_node;
        //Record* r=new Record()
        r_node=uf->MakeSet(counter,r_add);
        if (!r_node){
            delete r_add;
            return StatusType::ALLOCATION_ERROR;
        }
        counter++;

    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if(c_id<0||phone<0) return StatusType::INVALID_INPUT;
    Costumer *c_add= new Costumer(c_id,phone);
    Node<Costumer*>* c_n;
	c_n=costumers_hash_table->findNode(c_id, c_add);
	if(c_n!=nullptr){
		delete c_add;
		return StatusType::ALREADY_EXISTS;
	}
    costumers_hash_table->Insert(c_id,c_add);
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id<0) return StatusType::INVALID_INPUT;
    Costumer *c=new Costumer(c_id);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id, c));
	if((costumer)==nullptr){
		delete c;
		return StatusType::DOESNT_EXISTS;
	}
	int phone=(costumer)->phone;
	delete c;

	return phone;
    


}

StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id<0) return StatusType::INVALID_INPUT;
    Costumer *c=new Costumer(c_id);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id, c));
    delete c;

	if((costumer)==nullptr){
		
		return StatusType::DOESNT_EXISTS;
	}
    if (costumer->member==true)
    {
        return StatusType::ALREADY_EXISTS;
    }
    try
    {
        this->club_members->insert(costumer,0);
    }
    catch(const std::exception& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
	costumer->member=true;

    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if(c_id<0) return StatusType::INVALID_INPUT;
    Costumer *c=new Costumer(c_id);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id, c));
    delete c;
	if((costumer)==nullptr){
		return StatusType::DOESNT_EXISTS;
	}
    
return costumer->member;

}

StatusType RecordsCompany::buyRecord(int c_id,int r_id)
{
    
    if(c_id<0||r_id<0) return StatusType::INVALID_INPUT;
    if(this->uf->recordss_array->filled <=r_id) return StatusType::DOESNT_EXISTS;
     Costumer *c=new Costumer(c_id);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id, c));
    delete c;

	if((costumer)==nullptr){
		
		return StatusType::DOESNT_EXISTS;
	}
    if (costumer->member==true)
    {
        costumer->expenses=costumer->expenses+(uf->recordss_array->array[r_id]->purchases)+100;
    }
    (uf->recordss_array->array[r_id]->purchases)=(uf->recordss_array->array[r_id]->purchases)+1;
    return StatusType::SUCCESS;

}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1<0||c_id1>c_id2||amount<1)
    {
        return StatusType::INVALID_INPUT;
    }
    
    Costumer *c1=new Costumer(c_id1);
    if(c1==nullptr) 
       return StatusType::ALLOCATION_ERROR;
       
         GenericNode<Costumer*>* node1 = nullptr;
    //     node = node->createNode(c1);
     Costumer *c2=new Costumer(c_id2-1);

    if(c2==nullptr){
        delete c1;
		return StatusType::ALLOCATION_ERROR;
    }
    GenericNode<Costumer*>* node2 = nullptr;
    node2 = node2->createNode(c2);
    club_members->addExtraToAllUnder(club_members->root,node2,amount);
    int ranke=club_members->numOfEmps(club_members->root,c1);
    
    if(ranke>0){
    node1= club_members->select(ranke,club_members->root);
    //node1->extraGrade+=amount;
    }
    club_members->addExtraToAllUnder(club_members->root,node1,-amount);
    Costumer *c=new Costumer(c_id1);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id1, c));
    delete c;

	if((costumer)){
		
		if(costumer->member){
            costumer->expenses-=amount;
        }
	}
    // delete node1;
     delete node2;
    delete c1;
    delete c2;

    
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if(c_id<0) return StatusType::INVALID_INPUT;
    
     Costumer *c=new Costumer(c_id);
    if(c==nullptr)
		return StatusType::FAILURE;
    Costumer* costumer;
	(costumer)=(costumers_hash_table->findData(c_id, c));
    delete c;

	if((costumer)==nullptr){
		
		return StatusType::DOESNT_EXISTS;
	}
    if (costumer->member==false)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return -(club_members->getExtraTo(costumer))+(costumer->expenses);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if(r_id1<0||r_id2<0 ) {
        return StatusType::INVALID_INPUT;
    }
    if(r_id1>=counter ||r_id2>=counter) {
        return StatusType::DOESNT_EXISTS;
    }
    int to_return_h,to_return_col;
    if(uf->find(r_id1,&to_return_h,&to_return_col)->r_id==uf->find(r_id2,&to_return_h,&to_return_col)->r_id){
        return StatusType::FAILURE;
    }
    uf->Union(r_id1,r_id2);
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if(r_id<0 || !column || !hight) {
        return StatusType::INVALID_INPUT;
    }
    if(r_id>=counter) {
        return StatusType::DOESNT_EXISTS;
    }
    if(!uf->find(r_id,hight,column)){
        return StatusType::DOESNT_EXISTS;
    }
    else{
        return StatusType::SUCCESS;
    }

    return StatusType::SUCCESS;
}
