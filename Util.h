//
// Created by yennifer on 3/21/24.
//

#ifndef CONTACTS_MANAGER_UTIL_H
#define CONTACTS_MANAGER_UTIL_H
#include <string>

class Util {
private:
    void printGetter();
public:
    std::string* getLectura();
    void enterContinue();
    void clearConsole();
    int getNumber();
    int getNaturalNumber(int min, int max);
    void printSeparator();
};


#endif //CONTACTS_MANAGER_UTIL_H
