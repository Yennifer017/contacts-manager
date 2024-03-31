//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_LINKEDLIST_H
#define CONTACTS_MANAGER_LINKEDLIST_H

#include "Node.h"
#include <stdexcept>
template <class T>
class LinkedList {
private:

    /* METHODS */
    void insertWhenEmpty(Node<T>* &node){
        firstElement = node;
        lastElement = node;
    }
protected:
    void setSize(int _size){
        this->size = _size;
    }
    void setFirstElement(Node<T>* &_firstElement){
        this->firstElement = _firstElement;
    }
    void setLastElement(Node<T>* &_lastElement){
        this->lastElement = _lastElement;
    }

    /* ATRIBUTES */
    Node<T>* firstElement;
    Node<T>* lastElement;
    int size;

public:
    /* CONSTRUCTORES*/
    LinkedList(){
        firstElement = nullptr;
        lastElement = nullptr;
        size = 0;
    }

    /* METHODS */
    int getSize(){
        return size;
    }
    bool isEmpty(){
        return size == 0;
    }

    //OBTENER
    Node<T>* get(int position){
        if(position>=size || position<0){
            throw std::out_of_range("Error: No se puede acceder al elemento de la lista");
        }else if(position == 0){
            return firstElement;
        }else if(position == size - 1){
            return lastElement;
        }else{
            int half = size/2;
            Node<T>* current;
            if(position<=half){
                current = firstElement;
                for (int i = 0; i < position; ++i) {
                    current =  current->getNext();
                }
            }else{
                current = lastElement;
                for (int i = size-1; i > position; --i) {
                    current = current->getBefore();
                }
            }
            return current;
        }
    }
    // INSERTS
    void insertLast(Node<T>* &node, bool forceEmptyReferences){
        if(forceEmptyReferences){
            node->emptyReferences();
        }
        if(this->isEmpty()){
            insertWhenEmpty(node);
        }else{
            node->setBefore(lastElement);
            lastElement->setNext(node);
            lastElement = node;
        }
        size++;
    }
    void insertLast(T* element){
        Node<T>* newNode =  new Node(element);
        this->insertLast(newNode, false);
    }
    void insertLast(Node<T>* &node){
        this->insertLast(node, true);
    }
    void insertFirst(Node<T>* &node, bool forceEmptyReferences){
        if(forceEmptyReferences){
            node->emptyReferences();
        }
        if(this->isEmpty()){
            insertWhenEmpty(node);
        }else{
            node->setNext(firstElement);
            firstElement->setBefore(node);
            firstElement = node;
        }
        size++;
    }
    void insertFirst(T element){
        Node<T>* newNode =  new Node(element);
        this->insertFirst(newNode, false);
    }
    void insertFirst(Node<T>* &node){
        this->insertFirst(node, true);
    }
    void insert(Node<T>* &node, int position){
        if(position == size){
            this->insertLast(node, true);
        }else if(position == 0){
            this->insertFirst(node, true);
        }else if(position>0 && position<=size){
            Node<T>* left = get(position-1);
            Node<T>* right = left->getNext();
            left->setNext(node);
            node->setBefore(left);
            right->setBefore(node);
            node->setNext(right);
            size++;
        }else{
            throw std::out_of_range("Error: No se puede acceder al elemento de la lista");
        }
    }
    void insert(T element, int position){
        Node<T>* newNode = new Node(element);
        this->insert(newNode, position);
    }
    //DELETES
    Node<T>* deleteFirst(){
        if(this->isEmpty()){
            throw std::out_of_range("Error: No se puede eliminar el primero de una lista vacia");
        }else{
            Node<T>* deleted = firstElement;
            firstElement = firstElement->getNext();
            if(firstElement != nullptr){
                firstElement->setBefore(nullptr);
            }else{
                lastElement = nullptr;
            }
            size--;
            return deleted;
        }
    }
    Node<T>* deleteLast(){
        if(this->isEmpty()){
            throw std::out_of_range("Error: No se puede eliminar el ultimo de una lista vacia");
        }else{
            Node<T>* deleted = lastElement;
            lastElement = lastElement->getBefore();
            if(lastElement != nullptr){
                lastElement->setNext(nullptr);
            }else{
                firstElement = nullptr;
            }
            size--;
            return deleted;
        }
    }
    Node<T>* deleteElement(int position){
        if(position==0){
            return this->deleteFirst();
        }else if(position== size-1){
            return this-> deleteLast();
        }else if(position>0 && position < size-1){
            Node<T>* left = get(position-1);
            Node<T>* deleted = left->getNext();
            Node<T>* right = deleted->getNext();
            left->setNext(right);
            right->setBefore(left);
            return deleted;
        }else{
            throw std::out_of_range("Error: No se puede eliminar un elemento que no existe");
        }
    }

    //CORTAR
    virtual LinkedList<T>* split(int position){
        if(!this->isEmpty() && position > 0 && position<size){
            LinkedList<T>* newList = new LinkedList<T>();
            //obteniendo los elementos frontera del corte
            Node<T>* newBegin = get(position);
            Node<T>* last = newBegin->getBefore();
            //cortando referencias
            last->setNext(nullptr);
            newBegin->setBefore(nullptr);
            //inicializando la nueva lista
            newList->setFirstElement(newBegin);
            newList->setLastElement(this->lastElement);
            newList->setSize(size - position);
            //actualizando la lista actual
            this->lastElement = last;
            size = position;
            return newList;
        }else{
            throw std::out_of_range("Error: No se puede cortar la lista");
        }
    }
    //MERGE
    void merge(LinkedList<T>* list){
        if(list->isEmpty()){
            return; //no hay nada que hacer
        }
        this->size += list->size;
        if(this->isEmpty()){
            this->firstElement = list->firstElement;
            this->lastElement = list->lastElement;
        } else {
            this->lastElement->setNext(list->firstElement);
            list->firstElement->setBefore(lastElement);
            this->lastElement = list->lastElement;
        }
    }

    void clear(){
        this->size = 0;
        this->firstElement = nullptr;
        this->lastElement = nullptr;
    }

    ~LinkedList(){};
};


#endif //CONTACTS_MANAGER_LINKEDLIST_H
