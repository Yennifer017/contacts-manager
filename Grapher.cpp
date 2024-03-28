//
// Created by yennifer on 3/27/24.
//

#include "Grapher.h"

Grapher::Grapher() {
    groupTableGrapher = new HashTableGrapher<Group>();
    fieldTableGrapher = new HashTableGrapher<AVLtree<LinkedList<std::string>>>();
    treeGrapher = new TreeGraficator<LinkedList<std::string>>();

}

HashTableGrapher<Group> *Grapher::getGroupTableGrapher() {
    return this->groupTableGrapher;
}

HashTableGrapher<AVLtree<LinkedList<std::string>>> *Grapher::getFieldTableGrapher() {
    return this->fieldTableGrapher;
}

TreeGraficator<LinkedList<std::string>> *Grapher::getTreeGrapher() {
    return this->treeGrapher;
}
