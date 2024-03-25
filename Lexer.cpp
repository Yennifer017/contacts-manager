//
// Created by yennifer on 3/20/24.
//
#include <iostream>
#include "Lexer.h"
#include "TypeTkn.h"

LinkedList<Token> *Lexer::analizar(std::string *&texto) {
    tokens->clear();
    errors->clear();
    reading = new std::string();
    current = 0;
    while(current < texto->length()){
        if(!readAll){
            analiceChar(texto);
        }else{
            char currentChar = texto->at(current);
            reading->push_back(currentChar);
            if(currentChar == reading->at(0)){
                readAll = false;
                saveString();
            }
            current++;
        }
    }
    return tokens;
}

Lexer::Lexer() {
    this->reading = new std::string();
    tokens = new LinkedList<Token>();
    errors =  new LinkedList<std::string>();
    readAll = false;
    reguex = new Reguex();
}

void Lexer::analiceChar(std::string* &text) {
    char character = text->at(current);
    if(reguex->isLetter(character)){
        analizarIds(text);
    }else if(reguex->isNumber(character)){
        analizarNumbers(text);
    }else if (reguex->isReservedCharacter(character)){
        analizarSymbols(text);
    }else if(character == '"' || character == '\''){
        reading->push_back(character);
        readAll = true;
        current++;
    }else if(!reguex->isIgnoredCharacter(character)){
        std::string s(1, character);
        saveError(s);
    }else{
        current++;
    }
}

void Lexer::analizarIds(std::string* &text) {
    while(current < text->length() && reguex->isAlphanumeric(text->at(current))){
        reading->push_back(text->at(current));
        current++;
    }
    saveToken(getTypeId(reading));
}

void Lexer::analizarNumbers(std::string *&text) {
    while(current < text->length() && reguex->isNumber(text->at(current))){
        reading->push_back(text->at(current));
        current++;
    }
    saveToken(static_cast<int>(TypeTkn::ENTERO));
}

void Lexer::analizarSymbols(std::string *&text) {
    char currentChar = text->at(current);
    reading->push_back(currentChar);
    saveToken(getTypeSymbol(currentChar));
    current++;
}

int Lexer::getTypeId(std::string *&read) {
    if(read->compare("ADD") == 0){
        return static_cast<int>(TypeTkn::ADD);
    }else if(read->compare("NEW") == 0){
        return static_cast<int>(TypeTkn::NEW);
    }else if(read->compare("GROUP") == 0){
        return static_cast<int>(TypeTkn::GROUP);
    }else if(read->compare("FIELDS") == 0){
        return static_cast<int>(TypeTkn::FIELDS);
    }else if(read->compare("STRING") == 0){
        return static_cast<int>(TypeTkn::STRING_NAME);
    }else if(read->compare("INTEGER") == 0){
        return static_cast<int>(TypeTkn::INTEGER_NAME);
    }else if(read->compare("DATE") == 0){
        return static_cast<int>(TypeTkn::DATE_NAME);
    }else if(read->compare("CHAR") == 0){
        return static_cast<int>(TypeTkn::CHAR_NAME);
    }else if(read->compare("CONTACT") == 0){
        return static_cast<int>(TypeTkn::CONTACT);
    }else if(read->compare("FIND") == 0){
        return static_cast<int>(TypeTkn::FIND);
    }else if(read->compare("IN") == 0){
        return static_cast<int>(TypeTkn::IN);
    }else{
        return static_cast<int>(TypeTkn::ID);
    }
}

int Lexer::getTypeSymbol(char symbol) {
    switch (symbol) {
        case '=':
            return static_cast<int>(TypeTkn::IGUAL);
        case '(':
            return static_cast<int>(TypeTkn::PARENTESIS_L);
        case ')':
            return static_cast<int>(TypeTkn::PARENTESIS_R);
        case ',':
            return static_cast<int>(TypeTkn::COMA);
        case ';':
            return static_cast<int>(TypeTkn::FIN_INSTRUCCION);
        case '-':
            return static_cast<int>(TypeTkn::GUION);
        default:
            return -1;
    }
}

void Lexer::saveString() {
    if(reading->at(0) == '\'' && reading->length() !=3){
        std::string s = *reading;
        saveError(s);
    }else {
        saveToken(getTypeCadena(reading->at(0)));
    }
}

void Lexer::saveError(std::string lexem) {
    std::string *error = new std::string("Simbolo no reconocido <");
    error->append(lexem);
    error->append(">");
    errors->insertLast(error);
}

int Lexer::getTypeCadena(char symbol) {
    switch (symbol) {
        case '"':
            return static_cast<int>(TypeTkn::CADENA);
        case '\'':
            return static_cast<int>(TypeTkn::CARACTER);
        default:
            return -1;
    }
}

void Lexer::saveToken(int type) {
    Token* token = new Token(reading, type);
    tokens->insertLast(token);
    reading = new std::string ();
}

