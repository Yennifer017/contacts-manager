#include <iostream>
#include "Lexer.h"
#include "LinkedList.h"
#include "Token.h"
#include "HashTable.h"
#include "HashMap.h"

int main() {
    /*Lexer* lexer = new Lexer();
    std::string* text = new std::string("ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);");
    LinkedList<Token>* tokens = lexer->analizar(text);
    int index = 0;
    Node<Token> *current = tokens->get(index);
    while (current != nullptr){
        std::cout<<*current->getContent()->getLexema()<<"-type:";
        std::cout<<current->getContent()->getType()<<std::endl;
        current = current->getNext();
    }*/


    HashMap<std::string> *map = new HashMap<std::string>();
    map->insert(new std::string("adios"), new std::string("contenidoo 4"));
    map->insert(new std::string("hola"), new std::string("contenidoo 1"));
    map->insert(new std::string("clave1"), new std::string("contenidoo 2"));
    map->insert(new std::string("claveeee"), new std::string("contenidoo 3"));
    map->showKeys();

    //map->showKeys();
    std::cout<<*map->get(new std::string("hola"))->getContent()<<std::endl;

    return 0;
}
