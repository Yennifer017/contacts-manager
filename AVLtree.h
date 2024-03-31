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
    const int NOTHING = 0;
    const int RIGHT = 1;
    const int LEFT = -1;

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
        TreeNode<T>* rightToNewCurrent = newCurrent->getRight();
        newCurrent->setRight(current);
        current->emptyLeftReference();
        if(rightToNewCurrent != nullptr){
            current->setLeft(rightToNewCurrent);
            rightToNewCurrent->setFather(current);
            rightToNewCurrent->adjustWeight();
        }
        current->adjustWeight();
        current = newCurrent;
    }

    void rotateRightLeft(TreeNode<T>* &current){
        TreeNode<T>* middle = current->getRight();
        TreeNode<T>* last = middle->getLeft();
        middle->setFather(last);
        middle->emptyLeftReference();
        last->setFather(current);
        if(last->getRight() != nullptr){
            TreeNode<T>* originalRightLast = last->getRight();
            middle->setLeft(originalRightLast);
            originalRightLast->setFather(middle);
        }
        last->setRight(middle);
        current->setRight(last);
        middle->adjustWeight();
        last->adjustWeight();
        rotateLeftLeft(current);
    }

    void rotateLeftRight(TreeNode<T>* &current){
        TreeNode<T>* middle = current->getLeft();
        TreeNode<T>* last = middle->getRight();
        middle->setFather(last);
        middle->emptyRightReference();
        last->setFather(current);
        if(last->getLeft() != nullptr){
            TreeNode<T>* originalLeftLast = last->getLeft();
            middle->setRight(originalLeftLast);
            originalLeftLast->setFather(middle);
        }
        last->setLeft(middle);
        current->setLeft(last);
        middle->adjustWeight();
        last->adjustWeight();
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
        TreeNode<T>* leftToNewCurrent = newCurrent->getLeft();
        newCurrent->setLeft(current);
        current->emptyRightReference();
        if(leftToNewCurrent != nullptr){
            current->setRight(leftToNewCurrent);
            leftToNewCurrent->setFather(current);
            leftToNewCurrent->adjustWeight();
        }
        current->adjustWeight();
        current = newCurrent;
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
        int oneStep = NOTHING;
        int twoStep = NOTHING;
        while (currentNode != nullptr){ //hasta llegar a la raiz
            currentNode->adjustWeight();
            if(!currentNode->isBalanced()){
                int weight = currentNode->getInclinationWeight();
                if(weight > 0 && (oneStep == RIGHT && twoStep == RIGHT)
                    && currentNode->getRight() != nullptr && currentNode->getRight()->getRight() != nullptr){
                    rotateLeftLeft(currentNode);
                }else if(weight < 0 && (oneStep == LEFT && twoStep == LEFT)
                    && currentNode->getLeft() != nullptr && currentNode->getLeft()->getLeft() != nullptr){
                    rotateRightRight(currentNode);
                }else if(weight < 0 && (oneStep == LEFT && twoStep == RIGHT)
                    && currentNode->getLeft() != nullptr && currentNode->getLeft()->getRight() != nullptr){
                    rotateLeftRight(currentNode);
                }else if(weight > 0 && (oneStep == RIGHT && twoStep == LEFT)
                    && currentNode->getRight() != nullptr && currentNode->getRight()->getLeft() != nullptr){
                    rotateRightLeft(currentNode);
                }else{
                    std::cout<<"No se pudo balancear el arbol ERROR fatal"<<std::endl;
                }
            }
            twoStep = oneStep;
            oneStep = currentNode->isRightFromFather() ? RIGHT : LEFT;
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
    /*DESTRUCTOR*/
    ~AVLtree(){};
};


#endif //CONTACTS_MANAGER_AVLTREE_H
