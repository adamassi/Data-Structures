#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "linkedList.h"

template<class T>
class HashTable {
public:
    const  int INITIAL_SIZE =10;
    LinkedList<T> *table;
     int size;
     int filled;
    const  int expand_factor;

    HashTable(const  int &expand_factor = 2) : table(new LinkedList<T>[INITIAL_SIZE]), size(INITIAL_SIZE),filled(0), expand_factor(expand_factor) {}

    ~HashTable() {
        delete[] table;
    }

    int hashFunction(int index) {
        return index % 10;
    }

    Node<T> *findNode(int index, T data) {
        int i = hashFunction(index);
        Node<T> *currNode = table[i].getFirst();
        while (currNode) {
            if (*data == *(currNode->data)) {
                return currNode;
            }
            currNode = currNode->next;
        }
        return nullptr;
    }

    T findData(int index, T d){ 
        if (findNode(index, d) == nullptr) {
            return nullptr;
        }
        return findNode(index, d)->data; 
    }

    void extend() {
        int new_size = size * expand_factor;
        LinkedList<T> *new_array = new LinkedList<T>[new_size];

        for (int i = 0; i < size; i++) {
            Node<T> *currNode = table[i].getFirst();
            for (int j = 0; j < table[i].Len(); j++) {
                new_array[i].insert(currNode->data);
                currNode = currNode->next;
            }
        }
        delete[] table;
        table = new_array;
        size = new_size;
    }

    // inserts a key into hash table
    void Insert(int id, T data) {
        int index = hashFunction(id);
        if (findNode(index, data) != nullptr) {
            throw NodeAlreadyExists();
        }
        if (filled + 1 == size) {
            extend();
        }
        table[index].insert(data);
        filled++;
    }

    void Remove(int playerId, T data) {
        int index = hashFunction(playerId);
        if (findNode(index, data) == nullptr) {
            throw NodeDoesntExists();
        }
        table[index].remove(data);
        filled--;
    }

};

#endif


