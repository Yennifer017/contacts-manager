//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_NODE_H
#define CONTACTS_MANAGER_NODE_H

template <class T>
class Node {
private:
    T* content;
    Node<T> *next;
    Node<T> *before;
public:
    //constructores
    Node(T* content){
        this->content = content;
        this->next = nullptr;
        this->before = nullptr;
    };
    Node(T* content, Node<T>* next){
        this->content = content;
        this->next = next;
        this->before = nullptr;
    };
    Node(T* content, Node<T>* next, Node<T>* before){
        this->content = content;
        this->next = next;
        this->before = before;
    }

    /* METODOS */
    void emptyReferences(){
        this->next = nullptr;
        this->before = nullptr;
    }

    //GETTERS
    T* getContent(){
        return this->content;
    };
    Node<T>* getNext(){
        return this->next;
    };
    Node<T>* getBefore(){
        return this->before;
    }
    //SETTERS
    void setContent(T* _content){
        this->content = _content;
    }
    void setNext(Node<T>* _next){
        this->next = _next;
    }
    void setBefore(Node<T>* _before){
        this->before = _before;
    }
};


#endif //CONTACTS_MANAGER_NODE_H
