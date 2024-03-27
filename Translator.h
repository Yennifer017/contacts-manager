//
// Created by yennifer on 3/25/24.
//

#ifndef CONTACTS_MANAGER_TRANSLATOR_H
#define CONTACTS_MANAGER_TRANSLATOR_H

#include "HashMap.h"
#include "Group.h"
#include "LinkedList.h"
#include "Token.h"
#include "Node.h"
#include "TypeTkn.h"

class Translator {
private:
    HashMap<Group>* groups;
    void translateAddInstructions(LinkedList<Token>* &tokens, Node<Token>* &currentNode);

    std::string translateAddGroupStm(LinkedList<Token>* &tokens, Node<Token>* &current);
    std::string translateAddContactStm(LinkedList<Token>* &tokens, Node<Token>* &current);

    LinkedList<std::string>* convertData(LinkedList<Field>* fields, LinkedList<Token>* &data);
    void insertDataInTree( HashMap< AVLtree< LinkedList<std::string> > >* &tableGroup, LinkedList<std::string>* &data,
                           LinkedList<Field>* fields);
public:
    Translator(HashMap<Group>* &groups);
    void translate(LinkedList<Token>* &tokens);
};


#endif //CONTACTS_MANAGER_TRANSLATOR_H
