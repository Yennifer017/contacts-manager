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
    Util* util;
    Lexer* lexer;
    Reportero* reportero;
    HashMap<Group>* groups;
    Translator* translator;
    Exporter* exporter;
    Grapher* grapher;

    void terminal();
    void reportsMenu();
    void exportationMenu();
    void generateGraphicsMenu();
    void specificGraphMenu();

    void treeGraphMenu();

public:
    Manager();
    void showMenu();
};


#endif //CONTACTS_MANAGER_MANAGER_H
