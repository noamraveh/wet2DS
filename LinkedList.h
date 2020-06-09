#ifndef WET2DS_LINKEDLIST_H
#define WET2DS_LINKEDLIST_H
#include <algorithm>
#include <cstdbool>

template <class T>
class ListNode{
public:
    int key;
    T* data;
    ListNode* next;
    ListNode* prev;
    ListNode(int key,T* data): key(key),data(data),next(nullptr),prev(nullptr){}
    ListNode() = default;
    ~ListNode(){
        delete data;
    }
    int getKey(){
        return key;
    }
    T* getData(){
        return data;
    }
};

template <class T>
class LinkedList{
private:
    int num_of_nodes;
    ListNode<T>* first;

public:
    //c'tor
    LinkedList(): num_of_nodes(0),first(nullptr){}
    //d'tor
    ~LinkedList(){
        while (first != nullptr){
            ListNode<T>* temp = first;
            first = first->next;
            delete temp;
        }
    }
    //getFirst
    ListNode<T>* getFirstNode(){
        return first;
    }
    //getNext
    ListNode<T>* getNextNode(ListNode<T>* node){
        return node->next;
    }
    //getPrev
    ListNode<T>* getPrevNode(ListNode<T>* node){
        return node->prev;
    }

    //insert first
    ListNode<T>* InsertFirst(int key, T* data){
        auto node = new ListNode<T>(key,data);
        if (isEmpty()){
            first = node;
            node->prev = nullptr;
            node->next = nullptr;
        }
        else{  // there are already some nodes in the linked list
            node->prev = nullptr;
            node->next = first;
            first->prev = node;
            first = node;
        }
        num_of_nodes++;
        return node;
    }

    //removeNode
    void removeNode (int key){
        ListNode<T>* node = FindNode(key);
        if (!node){
            return;
        }
        if (node == first){ //delete first node
            if (!node->next){ //if it is the only node in the list
                delete node;
                first = nullptr;
            }
            else{
                node->next->prev = nullptr;
                first = node->next;
                delete node;
            }
            num_of_nodes--;
            return;
        }
        else if (node->next == nullptr){ //delete last node
            node->prev->next = nullptr;
            delete node;
            num_of_nodes--;
            return;
        }
        else { // delete middle node
            node->next->prev = node->prev;
            node->prev->next = node->next;
            delete node;
            num_of_nodes--;
        }
    }
    //IsEmpty
    bool isEmpty(){
        return (!first);
    }

    ListNode<T>* FindNode (int key){
        ListNode<T>* search_node = getFirstNode();
        if (!search_node){
            return nullptr;
        }
        if (search_node->key == key){
            return search_node;
        }
        while (search_node->next != nullptr){
            if (search_node->key == key){
                return search_node;
            }
            else{
                search_node = search_node->next;
            }
        }
        return nullptr;
    }
};
#endif //WET2DS_LINKEDLIST_H