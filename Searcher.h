//
// Created by yennifer on 3/28/24.
//

#ifndef CONTACTS_MANAGER_SEARCHER_H
#define CONTACTS_MANAGER_SEARCHER_H

#include <stdexcept>
#include "TreeNode.h"
#include "AVLtree.h"

template <class T>
class Searcher {
public:
    TreeNode<T>* find(std::string* keyToSearch, TreeNode<T>* treeNode){
        if(treeNode != nullptr){
            int comparation = keyToSearch->compare(*treeNode->getKey());
            if(comparation < 0){ //lado izquierdo
                if(treeNode->getLeft() != nullptr){
                    TreeNode<T>* left = treeNode->getLeft();
                    return find(keyToSearch, left);
                }
            } else if (comparation >0){ //lado derecho
                if(treeNode->getRight() != nullptr){
                    TreeNode<T>* right = treeNode->getRight();
                    return find(keyToSearch, right);
                }
            } else { //igualdad
                return treeNode;
            }
            throw std::invalid_argument("No se encontro el elemento");
        } else{
            throw std::runtime_error("No se puede acceder a un nodo de arbol vacio");
        }
    }

    TreeNode<T>* find(std::string* keyToSearch, AVLtree<T>* &tree){
        return find(keyToSearch, tree->getRaiz());
    }
};


#endif //CONTACTS_MANAGER_SEARCHER_H
