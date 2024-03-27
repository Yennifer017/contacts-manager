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
                translateAddInstructions(tokens, currentNode);
                break;
            case static_cast<int>(TypeTkn::FIND) :
                break;
            default:
                currentNode = currentNode->getNext(); //para pasar en caso se quede suspendido
        }
        currentNode = currentNode->getNext();
    }
}

std::string Translator::translateAddGroupStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
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
    current = current->getNext(); //para parar en el punto y coma
    Group* group = new Group(fields);
    groups->insert(nameGroup, group);
    return "Grupo <" + *nameGroup + "> agregado exitosamente\n";
}

std::string Translator::translateAddContactStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
    current = current->getNext()->getNext()->getNext(); //para apuntar al nombre del grupo
    std::string* nameGroup = current->getContent()->getLexema();
    Group* currentGroup = groups->get(nameGroup)->getContent();
    LinkedList<Token>* data = new LinkedList<Token>();
    current = current->getNext()->getNext()->getNext(); //para apuntar al primer dato
    while (current->getContent()->getType() != static_cast<int>(TypeTkn::PARENTESIS_R) ){
        if(current->getContent()->getType() != static_cast<int>(TypeTkn::COMA)){
            //TODO: guardar bien las fechas
            Node<Token>* tokenNodeCurrent = current;
            current = current->getNext();
            data->insertLast(tokenNodeCurrent, true);
        }else{
            current = current->getNext();
        }
    }
    LinkedList<std::string>* contactInformation = convertData(currentGroup->getFields(), data);
    HashMap< AVLtree< LinkedList<std::string> > > *tableIformation = currentGroup->getHashTable();
    insertDataInTree(tableIformation, contactInformation, currentGroup->getFields());
    current = current->getNext(); //para parar en el punto y coma
    return "contacto agregado exitosamente en " + *nameGroup;
}

void Translator::translateAddInstructions(LinkedList<Token>* &tokens, Node<Token>* &currentNode) {
    switch (currentNode->getNext()->getContent()->getType()) {
        case static_cast<int>(TypeTkn::NEW):
            try {
                std::cout<<translateAddGroupStm(tokens, currentNode)<<std::endl;
            }catch (const std::invalid_argument& e) {
                std::cout<<"El nombre de un grupo que se desea ingresar ya existe"<<std::endl;
            }
            break;
        case static_cast<int>(TypeTkn::CONTACT):
            try {
                std::cout<<translateAddContactStm(tokens, currentNode)<<std::endl;
            } catch (const std::invalid_argument& e) {
                std::cout<<e.what()<<std::endl;
            }
            break;
        default:
            throw std::invalid_argument("Errores sintacticos encontrados");
    }
}

LinkedList<std::string> *Translator::convertData(LinkedList<Field> *fields, LinkedList<Token> *&data) {
    LinkedList<std::string>* dataConverted = new LinkedList<std::string>();
    if(data->getSize() != fields->getSize()){
        throw std::invalid_argument("La cantidad de datos no concuerda");
    }
    Node<Field>* currentField = fields->get(0);
    Node<Token>* currenTkn = data->get(0);
    while (currentField != nullptr){
        if(!currentField->getContent()->isCompatibleType(currenTkn->getContent()->getType())){
            std::string error = "El dato de la instruccion <";
            error += *currenTkn->getContent()->getLexema();
            error += "> no concuerda en tipo";
            throw std::invalid_argument(error);
        }
        dataConverted->insertLast(currenTkn->getContent()->getLexema());
        currenTkn = currenTkn->getNext();
        currentField = currentField->getNext();
    }
    return dataConverted;
}

void Translator::insertDataInTree(HashMap<AVLtree<LinkedList<std::string>>>* &tableGroup, LinkedList<std::string>* &data,
                                  LinkedList<Field>* fields) {
    Node<Field>* currentField = fields->get(0);
    Node<std::string>* dataNode = data->get(0);
    while (currentField != nullptr){
        AVLtree<LinkedList<std::string>> *tree = tableGroup->get(currentField->getContent()->getName())->getContent();
        std::string* keyTree = dataNode->getContent();
        tree->insert(keyTree, data);
        dataNode = dataNode->getNext();
        currentField = currentField->getNext();
    }
}
