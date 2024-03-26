//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_LEXER_H
#define CONTACTS_MANAGER_LEXER_H
#include "LinkedList.h"
#include "Token.h"
#include "Reguex.h"


class Lexer {
private:
    int current;
    bool readAll;
    Reguex* reguex;
    std::string* reading;
    LinkedList<Token>* tokens;
    LinkedList<std::string>* errors;

    void analizarIds(std::string* &text);
    void analizarNumbers(std::string* &text);
    void analizarSymbols(std::string* &text);;
    void saveString();
    void saveError(std::string lexem);

    int getTypeId(std::string* &read);
    int getTypeSymbol(char symbol);
    int getTypeCadena(char symbol);

    void saveToken(int type);

public:
    Lexer();
    LinkedList<Token>* analizar(std::string* &texto);
    void analiceChar(std::string* &text);

    void showTokens();
};


#endif //CONTACTS_MANAGER_LEXER_H
