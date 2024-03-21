//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_TOKEN_H
#define CONTACTS_MANAGER_TOKEN_H
#include <string>

class Token {
private:
    std::string* lexema;
    int type;

public:
    Token(std::string* &_lexema, int type);
    std::string* getLexema();
    int getType();
};


#endif //CONTACTS_MANAGER_TOKEN_H
