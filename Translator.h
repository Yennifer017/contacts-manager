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
    void translateAddGroupStm(LinkedList<Token>* &tokens, Node<Token>* &current);
    void translateAddContactStm(LinkedList<Token>* &tokens, Node<Token>* &current);
public:
    Translator(HashMap<Group>* &groups);
    void translate(LinkedList<Token>* &tokens);
};


#endif //CONTACTS_MANAGER_TRANSLATOR_H
