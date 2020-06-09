//todo change ifndefs
#ifndef SOUNDCLOUD_HASHTABLE_H
#define SOUNDCLOUD_HASHTABLE_H
#include "LinkedList.h"
#include <algorithm>
#include <cstdbool>

template <class T>
class HashTable{
private:
    int num_occupied;
    int size;
    int init_size;
    LinkedList<T>** table;
    void resize(int updated_size){
        LinkedList<T>** old_table = table;
        table = new LinkedList<T>* [updated_size];
        for (int i=0; i<updated_size;i++){
            table[i] = nullptr;
        }
        int old_size = size;
        size =updated_size;
        for (int i=0; i<old_size; i++){
            if (old_table[i] != nullptr){
                ListNode<T>* node = old_table[i]->getFirstNode();
                while(node != nullptr){
                    insert(node->getKey(),node->getData());
                    int to_delete = node->getKey();
                    node = old_table[i]->getNextNode(node);
                    old_table[i]->removeNode(to_delete);
                }
            }
            delete old_table[i];
        }
        delete []old_table;
    }

    int hashFunc(int value){
        return value% this->size;
    }

public:
    //ctor
    HashTable(int init_size):num_occupied(0),size(init_size),init_size(init_size),table(nullptr){
        table = new LinkedList<T>*[size];
        for (int i=0; i<size;i++){
            table[i] = nullptr;
        }
    }
    //dtor
    ~HashTable(){
        for (int i = 0; i<size;i++){
            if (table[i]!= nullptr){
                delete table[i];
            }
        }
        delete []table;
    }
    //insert to table
    //TODO add alloc errors
    void insert(int key, T* data) {
        int index = hashFunc(key);
        if (table[index] == nullptr) {
            table[index] = new LinkedList<T>;
        }
        table[index]->InsertFirst(key,data);
        num_occupied++;
        if(num_occupied==size){
            resize(2*size);
        }
    }
    //Remove from table
    //todo add alloc errors
    //will be called only after element was found
    void remove (int key){
        int index = hashFunc(key);
        table[index]->removeNode(table[index]->FindNode(key)->getKey());
        num_occupied--;
        if (table[index]->isEmpty()){
            delete table[index];
            table[index] = nullptr;
        }
        if(num_occupied == size/4 && size > 2*init_size){
            resize(size/2);
        }
    }
    T* find(int key){
        int index = hashFunc(key);
        if (table[index]){
            return table[index]->FindNode(key)->getData();
        }
        return nullptr;
    }

};
#endif //SOUNDCLOUD_HASHTABLE_H
