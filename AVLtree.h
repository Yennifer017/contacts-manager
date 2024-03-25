//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_AVLTREE_H
#define CONTACTS_MANAGER_AVLTREE_H

#include "TreeNode.h"
template <class T>
class AVLtree {
private:
    TreeNode<T>* raiz;
    int totalElements;

    void internalInsertion(TreeNode<T>* &newNode){
        TreeNode<T>* auxiliar = raiz;
        bool inserted = false;
        do {
            int comparation = newNode->getKey()->compare(*auxiliar->getKey());
            if(comparation <= 0){//lado izquierdo
                if(auxiliar->getLeft() == nullptr){
                    newNode->setFather(auxiliar);
                    auxiliar->setLeft(newNode);
                    inserted = true;
                }else{
                    auxiliar = auxiliar->getLeft();
                }
            } else{ //lado derecho
                if(auxiliar->getRight() == nullptr){
                    newNode->setFather(auxiliar);
                    auxiliar->setRight(newNode);
                    inserted = true;
                }else{
                    auxiliar = auxiliar->getRight();
                }
            }
        } while (!inserted);
    }

    void balance(TreeNode<T>* &recentInserted){
        TreeNode<T>* currentNode = recentInserted;
        while (currentNode != nullptr){ //hasta llegar a la raiz
            if(!currentNode->isBalanced()){
                printf("Se encontro un nodo que no esta balanceado :c");
            }
            currentNode = currentNode->getFather();
        }
    }

public:
    /*CONSTRUCTOR*/
    AVLtree(){
        totalElements = 0;
    }

    /*METHODS*/
    bool isEmpty(){
        return this->raiz == nullptr;
    }
    void insert(std::string* &key, T* &content){
        TreeNode<T>* newNode = new TreeNode<T>(key, content);
        if(this->isEmpty()){
            raiz = newNode;
        }else{
            internalInsertion(newNode);
            this->balance(newNode);
        }
        totalElements ++;
    }

    int getTotalElements(){
        return this->totalElements;
    }

    TreeNode<T>* getRaiz(){
        return this->raiz;
    }
};


#endif //CONTACTS_MANAGER_AVLTREE_H
