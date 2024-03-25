//
// Created by yennifer on 3/21/24.
//

#ifndef CONTACTS_MANAGER_HASHCONTAINER_H
#define CONTACTS_MANAGER_HASHCONTAINER_H
#include <string>

template <class T>
class HashContainer {
private:
    T* contenido;
    std::string* key;
public:
    /*CONSTRUCTOR*/
    HashContainer(std::string* &key, T* &content) : key(key), contenido(content) {
    }
    HashContainer() : key(new std::string("")), contenido(nullptr){}

    /*GETTERS*/
    T* getContent(){
        return this->contenido;
    }
    std::string* getKey(){
        return this->key;
    }
};


#endif //CONTACTS_MANAGER_HASHCONTAINER_H
