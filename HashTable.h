//
// Created by yennifer on 3/21/24.
//

#ifndef CONTACTS_MANAGER_HASHTABLE_H
#define CONTACTS_MANAGER_HASHTABLE_H

#include "HashContainer.h"
#include <string>

template <class T>
class HashTable {
public:
    /*CONSTRUCTOR*/
    HashTable(){
        this->size = 5;
        this->totalElements = 0;
        table = new HashContainer<T>[size];
    };

    /*METHODS*/
    int hashFunction(std::string* &key, int sizeArray){
        int number = 0;
        for (int i = 0; i < key->length(); ++i) {
            number += (key->at(i)*i);
        }
        return number % sizeArray;
    };

    void insert(std::string* &key, T* &content){
        if(totalElements > size*0.6){
            rehasing();
        }
        HashContainer<T>* contentHash = new HashContainer<T>(key, content);
        insert(table, contentHash, size);
    };
    T* get(std::string *key){
        bool trying = false;
        int initialIndex = this->hashFunction(key, size);
        int index = initialIndex;
        do{
            if(table[index].getKey() == nullptr){
                throw std::invalid_argument("No se encontro el elemento");
            }else if(table[index].getKey() != nullptr && table[index].getKey() == key){
                return table[index];
            }else {
                index ++;
                index = index > size? 0: index;
                trying = index == initialIndex;
            }
        }while(trying);
        throw std::invalid_argument("No se encontro el elemento");
    };

private:
    /*ATRIBUTES*/
    int size;
    HashContainer<T>* table;
    int totalElements;
    const int INCREMENT = 5;

    /*INTERNAL METHODS*/

    void rehasing(){
        HashContainer<T>* newTable = new HashContainer<T>[size+INCREMENT];
        for (int i = 0; i < size; ++i) {
            if(table[i].getKey() != nullptr){
                insert(newTable, reinterpret_cast<HashContainer<std::basic_string<char>> *&>(table[i]), size + INCREMENT);
            }
        }
        table = newTable;
        size += INCREMENT;
    };

    void insert(HashContainer<T>* &currentTable, HashContainer<T>* &content, int sizeTable){
        int index = hashFunction(content->getKey(), sizeTable);
        bool trying = false;
        do {
            if (currentTable[index] == nullptr) {
                currentTable[index] = content;
            } else if (currentTable[index] != nullptr && currentTable[index].getKey() == content->getKey()) {
                throw std::invalid_argument("La clave esta repetida, no se pudo insertar");
            } else if (currentTable[index] != nullptr && currentTable[index].getKey() != content->getKey()) {
                index++;
                index = index>sizeTable? 0: index;
                trying = true;
            }
        } while (trying);
    };

};



#endif //CONTACTS_MANAGER_HASHTABLE_H
