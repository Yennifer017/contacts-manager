//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_MANAGER_H
#define CONTACTS_MANAGER_MANAGER_H

#include "Util.h"
#include "LinkedList.h"
#include "Token.h"
#include "Lexer.h"

class Manager {
private:
    Util* util;
    Lexer* lexer;
    void terminal();
public:
    Manager();
    void showMenu();
};


#endif //CONTACTS_MANAGER_MANAGER_H
