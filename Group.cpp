//
// Created by yennifer on 3/25/24.
//

#include "Group.h"


LinkedList<Field> *Group::getFields() {
    return this->fields;
}

Group::Group(LinkedList<Field>* &fields) {
    this->fields = fields;
    this->hashTable = new HashMap< AVLtree< LinkedList<std::string> > >();
    initFields();
}

void Group::initFields() {
    Node<Field>* currentFieldNode = fields->get(0);
    while (currentFieldNode != nullptr){
        hashTable->insert(currentFieldNode->getContent()->getName(), new AVLtree<LinkedList<std::string>>());
        currentFieldNode = currentFieldNode->getNext();
    }
}

HashMap<AVLtree<LinkedList<std::string>>> *Group::getHashTable() {
    return this->hashTable;
}

std::string Group::getFieldsAndTypes() {
    std::string text = "";
    int index = 1;
    Node<Field>* fieldNode = fields->get(0);
    while (fieldNode != nullptr){
        text += std::to_string(index);
        text += "=[" + *fieldNode->getContent()->getName();
        text += "=" + fieldNode->getContent()->getNameType() + "] ";
        fieldNode = fieldNode->getNext();
        index++;
    }
    return text;
}

Group::~Group() {

}
