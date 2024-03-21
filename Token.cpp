//
// Created by yennifer on 3/20/24.
//

#include "Token.h"

Token::Token(std::string *&_lexema, int type) {
    this->lexema = _lexema;
    this->type = type;
}

std::string *Token::getLexema() {
    return this->lexema;
}

int Token::getType() {
    return this->type;
}
