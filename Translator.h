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
#include "Reportero.h"
#include "Searcher.h"

class Translator {
private:
    HashMap<Group>* groups;
    Reportero * reportero;
    Searcher<LinkedList<std::string>>* searcher;
    void translateAddInstructions(LinkedList<Token>* &tokens, Node<Token>* &currentNode);

    std::string translateAddGroupStm(LinkedList<Token>* &tokens, Node<Token>* &current);
    std::string translateAddContactStm(LinkedList<Token>* &tokens, Node<Token>* &current);
    std::string translateFindStm(LinkedList<Token>* &tokens, Node<Token>* &current);

    LinkedList<std::string>* convertData(LinkedList<Field>* fields, LinkedList<Token>* &data);
    void insertDataInTree( HashMap< AVLtree< LinkedList<std::string> > >* &tableGroup, LinkedList<std::string>* &data,
                           LinkedList<Field>* fields);

    std::string findInformation(std::string* key, LinkedList<Field>* &fieldsList, TreeNode<LinkedList<std::string>>* treeNode);
public:
    Translator(HashMap<Group>* &groups, Reportero* &_reportero);
    void translate(LinkedList<Token>* &tokens);
};


#endif //CONTACTS_MANAGER_TRANSLATOR_H
