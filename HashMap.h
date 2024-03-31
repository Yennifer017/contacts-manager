//
// Created by yennifer on 3/22/24.
//

#ifndef CONTACTS_MANAGER_HASHMAP_H
#define CONTACTS_MANAGER_HASHMAP_H

#include "HashContainer.h"
#include <string>
#include <stdexcept>
#include <iostream>

template <class T>
class HashMap {
private:
    /*ATRIBUTES*/
    int size;
    HashContainer<T>** table;
    int totalElements;
    const int INCREMENT = 5;

    /*INTERNAL METHODS*/
    int hashFunction(std::string* &key, int sizeArray){
        int number = 0;
        for (int i = 0; i < key->length(); ++i) {
            number += (key->at(i)*i);
        }
        int index = number % sizeArray;
        if(index >= 0 && index<sizeArray){
            return index;
        }else{
            return 0;
        }
    }

    void insertInternal(HashContainer<T>** &currentTable, HashContainer<T>* content, int sizeTable){
        std::string* key = content->getKey();
        int index = hashFunction(key, sizeTable);
        bool trying = false;
        do {
            HashContainer<T>* currentContFromT = currentTable[index];
            if (currentContFromT == nullptr) {
                currentTable[index] = content;
                trying = false;
            } else if (currentContFromT->getKey()->compare(*content->getKey()) == 0) {
                throw std::invalid_argument("La clave" + *content->getKey() + "esta repetida, no se pudo insertar");
            } else if (currentContFromT->getKey()->compare(*content->getKey()) != 0) {
                index++;
                index = index>=sizeTable? 0: index;
                trying = true;
            }
        } while (trying);
    }


    void rehasing(){
        int newSize = size + INCREMENT;
        HashContainer<T>** oldTable = table;
        table = new HashContainer<T>*[newSize];
        for (int i = 0; i < size; ++i) {
            HashContainer<T>* currentHashCont = oldTable[i];
            if(currentHashCont != nullptr){
                insertInternal(table, currentHashCont, newSize);
            }
        }
        size = newSize;
    };


public:
    /*CONSTRUCTOR*/
    HashMap(){
        size = 5;
        table = new HashContainer<T>*[size]; //inicializando un array de punteros
        totalElements = 0;
    }

    /*METHODS*/
    void insert(std::string* key, T* content){
        if(totalElements >= size*0.6){
            rehasing();
        }
        HashContainer<T>* contentHash = new HashContainer<T>(key, content);
        insertInternal(table, contentHash, size);
        totalElements++;
    };

    HashContainer<T>* get(std::string *key){
        bool trying;
        int initialIndex = this->hashFunction(key, size);
        int index = initialIndex;
        do{
            HashContainer<T>* currentCont = table[index];
            if(currentCont == nullptr){
                throw std::invalid_argument("No se encontro <" + *key + "> en la HashTable");
            }else if(currentCont->getKey()->compare(*key) == 0){
                return currentCont;
            }else {
                index ++;
                index = index >= size? 0: index;
                trying = index != initialIndex;
            }
        }while(trying);
        throw std::invalid_argument("No se encontro el elemento");
    };

    HashContainer<T>* get(int pos){
        if(pos < 0 || pos >= size){
            throw std::out_of_range("Error: No se puede acceder al elemento de la tabla hash");
        }
        return table[pos];
    };

    HashContainer<T>* getFirstNonNullData(){
        if(size == 0){
            throw std::invalid_argument("No hay datos no nulos");
        }
        HashContainer<T>* container;
        for (int i = 0; i < size; ++i) {
            container = get(i);
            if(container != nullptr){
                return container;
            }
        }
        return nullptr;
    };

    int getSize(){
        return this->size;
    }

    int getTotalElements(){
        return this->totalElements;
    }

    void showKeys(){
        for (int i = 0; i < size; ++i) {
            HashContainer<T>* currentCont = table[i];
            if(currentCont == nullptr){
                std::cout<<"__vacio__"<<i<<std::endl;
            }else{
                std::cout<<"La clave es "<<*currentCont->getKey()<<std::endl;
            }
        }
    }

    void showExistentKeys(){
        for (int i = 0; i < size; ++i) {
            HashContainer<T>* currentCont = table[i];
            if(currentCont != nullptr) {
                std::cout << "   ->" << *currentCont->getKey() << std::endl;
            }
        }
    }
    ~HashMap(){};

};


#endif //CONTACTS_MANAGER_HASHMAP_H
