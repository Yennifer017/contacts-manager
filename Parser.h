//
// Created by yennifer on 3/28/24.
//

#ifndef CONTACTS_MANAGER_PARSER_H
#define CONTACTS_MANAGER_PARSER_H

#include "LinkedList.h"
#include "Token.h"
#include "Node.h"
#include "TypeTkn.h"

class Parser {
private:
    Node<Token>* currentNode;
    LinkedList<std::string>* errors;
    LinkedList<Token>* listToken;

    void addError(std::string mss);

    void validateAddStm();
    void validateFindStm();

    void validateAddContactStm();
    void validateAddGroupStm();

    void validateCampsData();
    void validateInsertCamps();
    void validateOneData();
    void validateDate();

    bool isNameType(int type);

public:
    Parser();
    void analize(LinkedList<Token>* tokens);
    std::string getErrorsDisplay();
    LinkedList<std::string>* getErrors();

};


#endif //CONTACTS_MANAGER_PARSER_H
