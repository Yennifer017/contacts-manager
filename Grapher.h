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
    DotFileExecutor* dotFileExecutor;
    HashTableGrapher<Group>* groupTableGrapher;
    HashTableGrapher<AVLtree<LinkedList<std::string>>>* fieldTableGrapher;
    TreeGraficator<LinkedList<std::string>>* treeGrapher;

    std::string getConnectCode(std::string *nameFather, std::string *nameChild);
    std::string createNode(std::string name, std::string label);

    std::string getCodeOneGroup(std::string *nameGroup, HashMap<AVLtree<LinkedList<std::string>>>* &hashMapFields);
    std::string getCodeForAll(std::string* nameGroup, HashMap<Group>* &groups);

public:
    Grapher();
    HashTableGrapher<Group>* getGroupTableGrapher();
    HashTableGrapher<AVLtree<LinkedList<std::string>>>* getFieldTableGrapher();
    TreeGraficator<LinkedList<std::string>>* getTreeGrapher();

    std::string graphGroup(std::string* nameGroup, Group* group);
    std::string graphAll(std::string* namePrincipalGroup, HashMap<Group>* &groups);
};


#endif //CONTACTS_MANAGER_GRAPHER_H
