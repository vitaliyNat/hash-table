#include <iostream>
#include "list.h"
#include "array.h"
#include <string>
#include <chrono>


using namespace std;

template <class K, class V>


class hashTable{
private:
    int maxSize;
    int size;
    dynamicArray<linkedList<K,V>> * arr;


    void createCopy(int Size){
        auto * tmpArr = new dynamicArray<linkedList<K,V>>();
        tmpArr->growSize(maxSize);
        for(int i = 0; i<maxSize;i++){
            auto* tmp1 = new linkedList<K,V>();
            tmpArr->addIndex(i,tmp1);
        }

        for(int i = 0; i< Size;i++){

            auto *tmp = arr->index(i)->getHead();
            if (tmp != nullptr)  {
                K tmpKey = tmp->key;
                V tmpValue = tmp->data;
                while (tmp != nullptr) {
                    tmpKey = tmp->key;
                    tmpValue = tmp->data;
                    tmpArr->index(hash(tmpKey))->push_tail(tmpKey, tmpValue);

                    tmp = tmp->next;
                }
            }
        }
        auto * tmp2 = arr;
        arr = tmpArr;
        delete tmp2;
    }


    void rehash(){
        if(size>2*maxSize){

            int oldSize = maxSize;
            maxSize= size*1.5;


            createCopy(oldSize);
        }
    }

public:
    hashTable<K,V>(){
        arr = new dynamicArray<linkedList<K,V>>();
        this->maxSize = 10;
         size = 0;
        arr->growSize(maxSize);
        for(int i = 0; i<maxSize;i++){
            auto* tmp = new linkedList<K,V>();
            arr->addIndex(i,tmp);
        }

    }



    int hash(string key){
        int length = key.length();
        int sum = 0;
        for(int i = 0; i< length;i++){
            sum +=key[i]*(31^(length-1));
        }
        if(sum<0) sum = -sum;
        return sum % maxSize;

    }

    void add(K key, V value){
        int tmpKey = hash(key);
       auto* tmpl =  arr->index(tmpKey);
        if(tmpl->searchNode(key)){
            tmpl->newValue(key,value);
        }else{
            tmpl->push_tail(key,value);
            size = size  + 1 ;
        }

        rehash();
    }

    void toString(){
        for(int i = 0; i< maxSize;i++){
            cout<<i<<": ";
            arr->index(i)->printList();
        }

        cout<<size<<" "<< maxSize;
    }

    Node<K,V> * search(K key){
        auto tmp = hash(key);
        return arr->index(tmp)->searchNode(key);
    }

    void deleteByKey(K key){
        auto tmp = hash(key);
        arr->index(tmp)->deleteNodeKey(key);
    }

    void clear(){
        for(int i = 0; i<maxSize;i++){
            arr->index(i)->clearList();
        }
        size = 0;
        int oldSize = maxSize;
        maxSize = 10;
        createCopy(oldSize);
    }

    void maxSizeList(){
        int mxsize = 0;
        int minsize = maxSize;
        int sum = 0;
        int nonEmpty = 0;

        for(int i =0; i<maxSize;i++){
            int tmp = arr->index(i)->getSize();
            if(tmp > mxsize){
                mxsize = tmp;
            }
            if(tmp<minsize && tmp !=0){
                minsize = tmp;
            }
            if(tmp !=0){
                sum+=tmp;
                nonEmpty++;
            }
        }
        int average = sum/nonEmpty;
        cout<<"Min length list: "<< minsize<<" Max length list: "<< mxsize<<" Average length non-empty list: "<< average<<" Non-empty list: "<<nonEmpty<<"Lists: "<<maxSize<<endl;

    }



};

int getRandomValue(){
    return rand() %10000;
}

string getRandomKey(){
    string abc = "abcduiiuiefg";
    for(int i = 0; i< abc.length();i++){
        unsigned char tmp = rand() % 57 + 65;
        while(tmp >91 && tmp < 97){
            tmp = rand() % 57 + 65;
        }
        abc[i]= tmp;
    }
    return abc;
};


int main() {
    auto first = new hashTable<string,int>();
    const int Qty = 100000;


    //Add begin
    auto t1 = chrono::high_resolution_clock::now();


    for (int i = 0; i < 10000; i++) {
        first->add(getRandomKey(),getRandomValue());
    }

    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("Add  %d elements: Time measured: %.3d nanoseconds.\n", Qty, duration.count());


    //Search element

    int hits = 0;
    t1 = chrono::high_resolution_clock::now();


    auto t1_temp = chrono::high_resolution_clock::now();
    auto t2_temp = chrono::high_resolution_clock::now();
    auto  duration_temp = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

    long duration_temp_data[Qty];
    auto worst_duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

    for (int i = 0; i < Qty; i++) {
        t1_temp = chrono::high_resolution_clock::now();



        if (first->search(getRandomKey())) {
            hits++;
        }





        t2_temp = chrono::high_resolution_clock::now();
        duration_temp = chrono::duration_cast<chrono::nanoseconds>(t2_temp - t1_temp);
        if (duration_temp > worst_duration) {
            worst_duration = duration_temp;
        }
        duration_temp_data[i] = duration_temp.count();


    }

    t2 = chrono::high_resolution_clock::now();
    long sum = 0;

    for (int i = 0; i < Qty; i++) {
        sum += duration_temp_data[i];
    }
    long average = sum / Qty;
    duration = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);
    printf("Searched  %d elements from %d : Time measured: %.3d nanoseconds.\n. Average time %.3d. Worst time %.d3", hits, Qty, duration.count(), average, worst_duration.count());

    cout << endl;
    first->maxSizeList();

    return 0;
}
