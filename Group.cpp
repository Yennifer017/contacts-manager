//
// Created by yennifer on 3/25/24.
//

#include "Group.h"

HashMap<AVLtree<Node<std::string>>> *Group::getHashTable() {
    return this->hashTable;
}

LinkedList<Field> *Group::getFields() {
    return this->fields;
}

Group::Group(LinkedList<Field>* &fields) {
    this->fields = fields;
    this->hashTable = new HashMap< AVLtree<Node<std::string>> >();
    initFields();
}

void Group::initFields() {
    Node<Field>* currentFieldNode = fields->get(0);
    while (currentFieldNode != nullptr){
        hashTable->insert(currentFieldNode->getContent()->getName(), new AVLtree<Node<std::string>>());
        currentFieldNode = currentFieldNode->getNext();
    }
}
