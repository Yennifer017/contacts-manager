//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_MANAGER_H
#define CONTACTS_MANAGER_MANAGER_H

#include "Util.h"
#include "LinkedList.h"
#include "Token.h"
#include "Lexer.h"
#include "HashMap.h"
#include "Group.h"
#include "Translator.h"
#include "Reportero.h"
#include "Exporter.h"
#include "Grapher.h"

class Manager {
private:
    std::string *GROUP_NAME;
    Util* util;
    Lexer* lexer;
    Reportero* reportero;
    HashMap<Group>* groups;
    Translator* translator;
    Exporter* exporter;
    Grapher* grapher;

    //principal functions menus
    void terminal();
    void reportsMenu();
    void exportationMenu();
    void generateGraphicsMenu();

    //graphs menus
    void specificGraphMenu();
    void groupGraphMenu();

    void treeGraphMenu();
    void fieldsGraphMenu();
    void groupTableGraphMenu();

public:
    Manager();
    void showMenu();
};


#endif //CONTACTS_MANAGER_MANAGER_H
