//
// Created by yennifer on 3/27/24.
//

#ifndef CONTACTS_MANAGER_GRAPHER_H
#define CONTACTS_MANAGER_GRAPHER_H
#include "HashTableGrapher.h"
#include "TreeGraficator.h"
#include "AVLtree.h"
#include "LinkedList.h"

class Grapher {
private:
    HashTableGrapher<Group>* groupTableGrapher;
    HashTableGrapher<AVLtree<LinkedList<std::string>>>* fieldTableGrapher;
    TreeGraficator<LinkedList<std::string>>* treeGrapher;

public:
    Grapher();
    HashTableGrapher<Group>* getGroupTableGrapher();
    HashTableGrapher<AVLtree<LinkedList<std::string>>>* getFieldTableGrapher();
    TreeGraficator<LinkedList<std::string>>* getTreeGrapher();
};


#endif //CONTACTS_MANAGER_GRAPHER_H
