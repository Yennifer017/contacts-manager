//
// Created by yennifer on 3/28/24.
//

#include "Parser.h"

Parser::Parser() {
    currentNode = nullptr;
    errors = new LinkedList<std::string>;
    listToken = new LinkedList<Token>;
}

void Parser::analize(LinkedList<Token> *tokens) {
    errors->clear();
    listToken = tokens;
    if(listToken->isEmpty()){
        errors->insertLast(new std::string("Se esperaba un ADD_stm o un FIND_stm"));
    }else{
        currentNode = listToken->get(0);
        while (currentNode != nullptr){
            switch (currentNode->getContent()->getType()) {
                case static_cast<int>(TypeTkn::ADD):
                    currentNode = currentNode->getNext(); //apunta al siguiente del add
                    validateAddStm();
                    break;
                case static_cast<int>(TypeTkn::FIND):
                    currentNode = currentNode->getNext(); //apunta al siguiente del find
                    validateFindStm();
                    break;
                default:
                    addError("Se esperaba un ADD o FIND");
            }
            if(currentNode != nullptr){
                currentNode = currentNode->getNext();
            }
        }
    }
}

std::string Parser::getErrorsDisplay() {
    if(errors->isEmpty()){
        return "__sin errores__";
    }else{
        std::string errorsDisplay = "";
        Node<std::string>* currentNode = errors->get(0);
        while (currentNode != nullptr){
            errorsDisplay += *currentNode->getContent() + "\n";
            currentNode = currentNode->getNext();
        }
        return errorsDisplay;
    }
}

void Parser::addError(std::string mss) {
    std::string message;
    if(currentNode != nullptr){
        message += "Cerca de: <" + *currentNode->getContent()->getLexema() + "> ";
    }
    message += mss;
    errors->insertLast(new std::string(message));
}

void Parser::validateAddStm() {
    if(currentNode != nullptr){
        bool trying = true;
        while (currentNode != nullptr && trying ){
            switch (currentNode->getContent()->getType()) {
                case static_cast<int>(TypeTkn::CONTACT):
                    validateAddContactStm();
                    trying = false;
                    break;
                case static_cast<int>(TypeTkn::NEW):
                    validateAddGroupStm();
                    trying = false;
                    break;
                default:
                    addError("Se esperaba CONTACT o NEW");
                    trying = true;
                    break;
            }
            if(currentNode != nullptr){
                currentNode = currentNode->getNext();
            }
        }
    }else{
        addError("Se esperaba CONTACT o NEW");
    }
}

void Parser::validateAddContactStm() {
    bool finished = false;
    int status = 0;
    while (currentNode != nullptr && !finished){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                status = 1; //aqui va el CONTACT, solo lo pasa
                break;
            case 1:
                if(type != static_cast<int>(TypeTkn::IN)) {
                    addError("Se esperaba IN");
                }
                status = 2;
                break;
            case 2:
                if(type != static_cast<int>(TypeTkn::ID)){
                    addError("Se esperaba un identificador");
                }
                status = 3;
                break;
            case 3:
                if(type != static_cast<int>(TypeTkn::FIELDS)){
                    addError("Se esperaba FIELDS");
                }
                status = 4;
                break;
            case 4:
                if(type != static_cast<int>(TypeTkn::PARENTESIS_L)){
                    addError("Se esperaba <<(>>");
                }
                status = 5;
                break;
            case 5:
                validateCampsData();
                status = 6;
                break;
            case 6:
                if(type != static_cast<int>(TypeTkn::PARENTESIS_R)){
                    addError("Se esperaba <<)>>");
                }
                status = 7;
                break;
            case 7:
                if(type != static_cast<int>(TypeTkn::FIN_INSTRUCCION)){
                    addError("Se esperaba <<;>>");
                }
                status = 8;
                break;
            default:
                finished = true;
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }
    } //end while
    if(status != 8){
        addError("Add_contact_statement incompleto / mal formado");
    }
}

void Parser::validateAddGroupStm() {
    bool finished = false;
    int status = 0;
    while (currentNode != nullptr && !finished){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                status = 1; //aqui va el NEW solo lo pasa
                break;
            case 1:
                if(type != static_cast<int>(TypeTkn::GUION)){
                    addError("Se esperaba GUION");
                }
                status = 2;
                break;
            case 2:
                if(type != static_cast<int>(TypeTkn::GROUP)){
                    addError("Se esperaba GROUP");
                }
                status = 3;
                break;
            case 3:
                if(type != static_cast<int>(TypeTkn::ID)){
                    addError("Se esperaba un identificador");
                }
                status = 4;
                break;
            case 4:
                if(type != static_cast<int>(TypeTkn::FIELDS)){
                    addError("Se esperaba FIELDS");
                }
                status = 5;
                break;
            case 5:
                if(type != static_cast<int>(TypeTkn::PARENTESIS_L)){
                    addError("Se esperaba <<(>>");
                }
                status = 6;
                break;
            case 6:
                validateInsertCamps();
                status = 7;
                break;
            case 7:
                if(type != static_cast<int>(TypeTkn::PARENTESIS_R)){
                    addError("Se esperaba <<)>>");
                }
                status = 8;
                break;
            case 8:
                if(type != static_cast<int>(TypeTkn::FIN_INSTRUCCION)){
                    addError("Se esperaba <<;>>");
                }
                status = 9;
                break;
            default:
                finished = true;
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }

    } //end while
    if(status != 9){
        addError("Add_group_statement incompleto / mal formado");
    }
}

void Parser::validateFindStm() {
    bool finished = false;
    int status = 0;
    while (currentNode != nullptr && !finished){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                if(type != static_cast<int>(TypeTkn::CONTACT)){
                    addError("Se esperaba CONTACT");
                }
                status = 1;
                break;
            case 1:
                if(type != static_cast<int>(TypeTkn::IN)){
                    addError("Se esperaba IN");
                }
                status = 2;
                break;
            case 2:
                if(type != static_cast<int>(TypeTkn::ID)){
                    addError("Se esperaba un identificador");
                }
                status = 3;
                break;
            case 3:
                if(type != static_cast<int>(TypeTkn::CONTACT)){
                    addError("Se esperaba CONTACT");
                }
                status = 4;
                break;
            case 4:
                if(type != static_cast<int>(TypeTkn::GUION)){
                    addError("Se esperaba <<->>");
                }
                status = 5;
                break;
            case 5:
                if(type != static_cast<int>(TypeTkn::FIELD)){
                    addError("Se esperaba FIELD");
                }
                status = 6;
                break;
            case 6:
                if(type != static_cast<int>(TypeTkn::ID)){
                    addError("Se esperaba un identificador");
                }
                status = 7;
                break;
            case 7:
                if(type != static_cast<int>(TypeTkn::IGUAL)){
                    addError("Se esperaba <<=>>");
                }
                status = 8;
                break;
            case 8:
                validateOneData();
                status = 9;
                break;
            default:
                finished = true;
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }
    } //end while
    if(status != 9){
        addError("Find_group_statement incompleto / mal formado");
    }
}

void Parser::validateInsertCamps() {
    int status = 0;
    bool running = true;
    while (currentNode != nullptr && running){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                if(type != static_cast<int>(TypeTkn::ID)){
                    addError("Se esperaba un identificador");
                }
                status = 1;
                break;
            case 1:
                if(!isNameType(type)){
                    addError("Se esperaba un nombre de un tipo");
                }
                if(currentNode->getNext() != nullptr){
                    status = 2;
                }
                break;
            case 2:
                if(type != static_cast<int>(TypeTkn::COMA)){
                    status = 1;
                    currentNode = currentNode->getBefore();
                    running = false;
                }else {
                    status = 0;
                }
                break;
            default:
                running = false;
                break;
        }
        if(currentNode != nullptr && running){
            currentNode = currentNode->getNext();
        }
    }
    if(status != 1){
        addError("Definicion de campos incompleto / mal formado");
    }
}

bool Parser::isNameType(int type) {
    return (type == static_cast<int>(TypeTkn::STRING_NAME))
           || (type == static_cast<int>(TypeTkn::CHAR_NAME))
           || (type == static_cast<int>(TypeTkn::DATE_NAME))
           || (type == static_cast<int>(TypeTkn::INTEGER_NAME));
}

void Parser::validateCampsData() {
    int status = 0;
    bool running = true;
    while (currentNode != nullptr && running){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                validateOneData();
                if(currentNode->getNext() != nullptr){
                    status = 1;
                }
                break;
            case 1:
                if(type != static_cast<int>(TypeTkn::COMA)){
                    status = 1;
                    running = false;
                }else {
                    status = 0;
                }
                break;
            default:
                running = false;
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }
    }
    if(status != 0){
        addError("Definicion de datos incompleto / mal formado");
    }

}

void Parser::validateDate() {
    bool finished = false;
    int status = 0;
    while (currentNode != nullptr && !finished){
        int type = currentNode->getContent()->getType();
        switch (status) {
            case 0:
                if(type != static_cast<int>(TypeTkn::ENTERO)){
                    addError("Se esperaba un entero");
                }
                status = 1;
                break;
            case 1:
                if(type != static_cast<int>(TypeTkn::GUION)){
                    addError("Se esperaba <<->>");
                }
                status = 2;
                break;
            case 2:
                if(type != static_cast<int>(TypeTkn::ENTERO)){
                    addError("Se esperaba un entero");
                }
                status = 3;
                break;
            case 3:
                if(type != static_cast<int>(TypeTkn::GUION)){
                    addError("Se esperaba <<->>");
                }
                status = 4;
                break;
            case 4:
                if(type != static_cast<int>(TypeTkn::ENTERO)){
                    addError("Se esperaba un entero");
                }
                status = 5;
                break;
            default:
                finished = true;
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }
    } //end while
    if(status != 5){
        addError("fecha incompleta / mal formada");
    }
}

void Parser::validateOneData() {
    if(currentNode != nullptr){
        int type = currentNode->getContent()->getType();
        switch (type) {
            case static_cast<int>(TypeTkn::ENTERO):
                if( (currentNode->getNext() != nullptr) && (currentNode->getContent()->getType() == static_cast<int>(TypeTkn::GUION)) ){
                    validateDate();
                }
                break;
            case static_cast<int>(TypeTkn::ID):
                //do nothing
                break;
            case static_cast<int>(TypeTkn::CADENA):
                //do nothing
                break;
            case static_cast<int>(TypeTkn::CARACTER):
                //do nothing
                break;
            default:
                addError("Se esperaba un dato");
                break;
        }
        if(currentNode != nullptr){
            currentNode = currentNode->getNext();
        }
    }else{
        addError("Se esperaba un dato");
    }
}

LinkedList<std::string> *Parser::getErrors() {
    return this->errors;
}


