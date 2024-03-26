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
            if(comparation < 0){//lado izquierdo
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

    void rotateRightRight(TreeNode<T>* &current){ //cuando ambos estan en la izquierda
        TreeNode<T>* newCurrent = current->getLeft();
        if(current->getFather() != nullptr){
            fixFatherReferences(current, newCurrent);
        }else{
            raiz = newCurrent;
            current->setFather(newCurrent);
            newCurrent->emptyFatherReference();
        }
        newCurrent->setRight(current);
        current->emptyLeftReference();
        current->adjustWeight();
    }

    void rotateRightLeft(TreeNode<T>* &current){
        TreeNode<T>* middle = current->getRight();
        TreeNode<T>* last = middle->getLeft();
        middle->setFather(last);
        middle->emptyLeftReference();
        last->setFather(current);
        last->setRight(middle);
        current->setRight(last);
        rotateLeftLeft(current);
    }

    void rotateLeftRight(TreeNode<T>* &current){
        TreeNode<T>* middle = current->getLeft();
        TreeNode<T>* last = middle->getRight();
        middle->setFather(last);
        middle->emptyRightReference();
        last->setFather(current);
        last->setLeft(middle);
        current->setLeft(last);
        rotateRightRight(current);
    }

    void rotateLeftLeft(TreeNode<T>* &current){ //cuando estan ambos a la derecha
        TreeNode<T>* newCurrent = current->getRight();
        if(current->getFather() != nullptr){
            fixFatherReferences(current, newCurrent);
        }else{
            raiz = newCurrent;
            current->setFather(newCurrent);
            newCurrent->emptyFatherReference();
        }
        newCurrent->setLeft(current);
        current->emptyRightReference();
        current->adjustWeight();
    }

    void fixFatherReferences(TreeNode<T>* &current,TreeNode<T>* &newCurrent){
        TreeNode<T>* father = current->getFather();
        bool wasRightFromFather = father->getRight() == current;
        current->setFather(newCurrent);
        newCurrent->setFather(father);
        if(wasRightFromFather){
            father->setRight(newCurrent);
        }else{
            father->setLeft(newCurrent);
        }
        father->adjustWeight();
    }

    void balance(TreeNode<T>* &recentInserted){
        TreeNode<T>* currentNode = recentInserted;
        while (currentNode != nullptr){ //hasta llegar a la raiz
            currentNode->adjustWeight();
            if(!currentNode->isBalanced()){
                if(currentNode->getRight() != nullptr && currentNode->getRight()->getRight() != nullptr){
                    rotateLeftLeft(currentNode);
                }else if(currentNode->getLeft() != nullptr && currentNode->getLeft()->getLeft() != nullptr){
                    rotateRightRight(currentNode);
                }else if(currentNode->getLeft() != nullptr && currentNode->getLeft()->getRight() != nullptr){
                    rotateLeftRight(currentNode);
                }else if(currentNode->getRight() != nullptr && currentNode->getRight()->getLeft() != nullptr){
                    rotateRightLeft(currentNode);
                }else{
                    std::cout<<"No se pudo balancear el arbol ERROR fatal";
                }
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
            balance(newNode);
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
