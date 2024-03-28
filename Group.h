//
// Created by yennifer on 3/25/24.
//

#ifndef CONTACTS_MANAGER_GROUP_H
#define CONTACTS_MANAGER_GROUP_H

#include "LinkedList.h"
#include "Field.h"
#include "HashMap.h"
#include "AVLtree.h"
#include "Node.h"

class Group {
private:
    LinkedList<Field>* fields;
    HashMap< AVLtree< LinkedList<std::string> > >* hashTable;
    void initFields();
public:
    Group(LinkedList<Field>* &fields);
    LinkedList<Field>* getFields();
    HashMap< AVLtree<LinkedList<std::string>> >* getHashTable();
    std::string getFieldsAndTypes();
};


#endif //CONTACTS_MANAGER_GROUP_H
