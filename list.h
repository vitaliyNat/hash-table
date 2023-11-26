#include <iostream>

using namespace std;

template <class K, class V>


class Node{
private:
    int id;
public:

    Node<K,V> * next;
    Node<K,V> * prev;
    K key;
    V data;
    Node<K,V>() {
        id  = 0;
        next = nullptr;
        prev = nullptr;
        this->key =0;
        data = 0;
    }

    Node<K,V>(K key, V value) {
        id  = 0;
        next = nullptr;
        prev = nullptr;
        this->key = key;
        data = value;
    }

    void setId(int id){
        this->id = id;
    }
    int getId(){
        return this->id;
    }



    void printNode(){
        if(this != nullptr){
            cout << "key: " <<this->key<<" value: "<< this->data<<endl;
        }else{
            cout<< "This node is NULL"<<endl;
        }
    }
};




template <class  K,class V>
class linkedList {
private:
    int size;
    Node<K,V> *head;
    Node<K,V> *tail;
    int idQty;


public:


    linkedList<K,V>() {
        idQty = 0;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }


    Node<K,V> *getHead() {
        return this->head;
    }

    int getSize() {
        return this->size;
    }

    void add_begin(K key,V value) {

        auto *newNode = new Node<K,V>(key,value);
        newNode->next = this->head;

        if (this->size == 0) {
            this->tail = newNode;
        } else {
            this->head->prev = newNode;
        }
        this->head = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;
    }

    void push_tail(K key,V value) {
        auto *newNode = new Node<K,V>(key,value);
        newNode->prev = this->tail;


        if (size < 1) {
            this->head = newNode;
        } else {
            this->tail->next = newNode;
        }

        this->tail = newNode;

        newNode->setId(this->idQty);
        this->idQty++;
        this->size++;
    }

    Node<K,V> *searchNode(K key) {
        auto *tmp = this->getHead();
        while (tmp != nullptr) {
            if (tmp->key == key) {
                return tmp;
            }
            tmp = tmp->next;
        }
        return nullptr;
    }


    void deleteNodeKey( K key) {
        auto *tmp =searchNode(key);

        if (tmp) {
            if(this->head == tmp && this->tail == tmp){
                this->clearList();

            }else
                if(this->head == tmp ){
                this->deleteFirst();
            }else
            if(this->tail == tmp ){
                this->deleteLast();
            }else{
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            this->size--;
            delete tmp;}


            cout << "Success delete" << endl;
        } else {
            cout << "Failed delete: invalid key" << endl;
        }
    }


    void deleteLast() {
        this->tail = this->tail->prev;
        delete this->tail->next;
        this->tail->next = nullptr;
        this->size--;
    }

    void deleteFirst() {
        this->head = this->head->next;
        delete this->head->prev;
        this->head->prev = nullptr;
        this->size--;
    }


    void newValue(K key, V value) {
        auto * tmp = searchNode(key);
        if (tmp) {
           tmp->data = value;
            cout << "Success new Value" << endl;
        } else {
            cout << "Failed new value: invalid index" << endl;
        }
    }

    void clearList() {
        while (size != 0) {
            if (this->size == 1) {
                delete this->head;
                this->head = nullptr;
                this->tail = nullptr;
                this->size = 0;
            } else {
                this->deleteFirst();
            }
        }
    }


    void printList() {
        auto *tmp = this->getHead();
        if (tmp == nullptr) {
            cout<< endl;
            return;
        }
        while (tmp != nullptr) {
            tmp->printNode();
            tmp = tmp->next;
        }
    }


};