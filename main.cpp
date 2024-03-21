#include <iostream>
#include "Lexer.h"
#include "LinkedList.h"
#include "Token.h"

int main() {
    Lexer* lexer = new Lexer();
    std::string* text = new std::string("ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);");
    LinkedList<Token>* tokens = lexer->analizar(text);
    int index = 0;
    Node<Token> *current = tokens->get(index);
    while (current != nullptr){
        printf("El token:");
        std::cout<<tokens->get(index)->getContent()->getLexema()<<std::endl;
        current = current->getNext();
    }
}
