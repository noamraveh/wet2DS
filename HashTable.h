//todo change ifndefs
#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H
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
    bool resize(int updated_size){
        LinkedList<T>** old_table = table;
        try{
            table = new LinkedList<T>* [updated_size];
        }
        catch(std::bad_alloc&){
            table = old_table;
            return false;
        }
        for (int i=0; i<updated_size;i++){
            table[i] = nullptr;
        }
        int old_size = size;
        size =updated_size;
        num_occupied = 0;
        for (int i=0; i<old_size; i++){
            if (old_table[i] != nullptr){
                ListNode<T>* node = old_table[i]->getFirstNode();
                while(node != nullptr){
                    insert(node->getKey(),node->getData());
                    node->clearData();
                    int to_delete = node->getKey();
                    node = old_table[i]->getNextNode(node);
                    old_table[i]->removeNode(to_delete);
                }
            }
            delete old_table[i];
        }
        delete []old_table;
        return true;
    }

    int hashFunc(int value){
        return value% this->size;
    }

public:
    //ctor
    explicit HashTable(int init_size):num_occupied(0),size(init_size),init_size(init_size),table(nullptr){
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
    bool insert(int key, T* data) {
        int index = hashFunc(key);
        if (table[index] == nullptr) {
            try{
                table[index] = new LinkedList<T>;
            }
            catch(std::bad_alloc&){
                return false;
            }
        }
        table[index]->InsertFirst(key,data);
        num_occupied++;
        if(num_occupied==size){
            if(!resize(2*size)){
                return false;
            }
        }
        return true;
    }
    //Remove from table
    //will be called only after element was found
    bool remove (int key){
        int index = hashFunc(key);
        table[index]->removeNode(table[index]->FindNode(key)->getKey());
        num_occupied--;
        if (table[index]->isEmpty()){
            delete table[index];
            table[index] = nullptr;
        }
        if(num_occupied == size/4 && size > 2*init_size){
            if(!resize(size/2)){
                return false;
            }
        }
        return true;
    }
    T* find(int key){
        int index = hashFunc(key);
        if (table[index]){
            ListNode<T>* temp = table[index]->FindNode(key);
            if (!temp)
                return nullptr;
            return temp->getData();
        }
        return nullptr;
    }

};
#endif //WET2DS_HASHTABLE_H
