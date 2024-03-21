//
// Created by yennifer on 3/20/24.
//

#include "Reguex.h"

bool Reguex::isUpperCase(char character) {
    return ((character >= 'a' && character <= 'z') || character == '_');
}

bool Reguex::isLowerCase(char character) {
    return (character >= 'A' && character <= 'Z');
}

bool Reguex::isLetter(char character) {
    return isUpperCase(character) || isLowerCase(character);
}

bool Reguex::isNumber(char character) {
    return (character >= '0' && character <= '9');
}

bool Reguex::isReservedCharacter(char character) {
    switch (character) {
        case '=':
            return true;
        case '-':
            return true;
        case '(':
            return true;
        case ')':
            return true;
        case ',':
            return true;
        case ';':
            return true;
        default:
            return false;
    }
}

bool Reguex::isIgnoredCharacter(char character) {
    switch (character) {
        case ' ':
            return true;
        case 9:
            return true;
        case '\r':
            return true;
        case '\n':
            return true;
        default:
            return false;
    }
}

bool Reguex::isAlphanumeric(char character) {
    return this->isLetter(character) || this->isNumber(character);
}
