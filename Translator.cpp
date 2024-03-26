//
// Created by yennifer on 3/25/24.
//

#include "Translator.h"

Translator::Translator(HashMap<Group> *&groups) {
    this->groups = groups;
}

void Translator::translate(LinkedList<Token>* &tokens) {
    Node<Token>* currentNode = tokens->get(0);
    while (currentNode != nullptr){
        switch (currentNode->getContent()->getType()) {
            case static_cast<int>(TypeTkn::ADD) :

                switch (currentNode->getNext()->getContent()->getType()) {
                    case static_cast<int>(TypeTkn::NEW):
                        translateAddGroupStm(tokens, currentNode);
                        break;
                    case static_cast<int>(TypeTkn::CONTACT):
                        translateAddContactStm(tokens, currentNode);
                        break;
                    default:
                        throw std::invalid_argument("Errores sintacticos encontrados");
                }

                break;
            case static_cast<int>(TypeTkn::FIND) :
                break;
            default:
                throw std::invalid_argument("Errores sintacticos encontrados");
        }
        currentNode = currentNode->getNext();
    }
}

void Translator::translateAddGroupStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
    LinkedList<Field>* fields = new LinkedList<Field>;
    current = current->getNext()->getNext()->getNext()->getNext(); //para apuntar al nombre del grupo
    std::string* nameGroup = current->getContent()->getLexema();
    current = current->getNext()->getNext()->getNext(); //para apuntar al primer campo de datos
    while (current->getContent()->getType() != static_cast<int>(TypeTkn::PARENTESIS_R)){
        if(current->getContent()->getType() != static_cast<int>(TypeTkn::COMA)){
            Field* field = new Field(current->getContent()->getLexema(), current->getNext()->getContent()->getType());
            fields->insertLast(field);
            current = current->getNext()->getNext(); //para irnos o a la coma o al parentesis
        }else{
            current = current->getNext();
        }
    }
    Group* group = new Group(fields);
    groups->insert(nameGroup, group);
    current = current->getNext(); //para parar en el punto y coma
}

void Translator::translateAddContactStm(LinkedList<Token> *&tokens, Node<Token> *&current) {

}
