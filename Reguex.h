//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_REGUEX_H
#define CONTACTS_MANAGER_REGUEX_H


class Reguex {
public:
    bool isUpperCase(char character);
    bool isLowerCase(char character);
    bool isLetter(char character);
    bool isNumber(char character);
    bool isAlphanumeric(char character);
    bool isReservedCharacter(char character);
    bool isIgnoredCharacter(char character);
    ~Reguex();

};


#endif //CONTACTS_MANAGER_REGUEX_H
