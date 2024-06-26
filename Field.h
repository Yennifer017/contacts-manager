//
// Created by yennifer on 3/25/24.
//

#ifndef CONTACTS_MANAGER_FIELD_H
#define CONTACTS_MANAGER_FIELD_H

#include <string>

class Field {
private:
    std::string* name;
    int type;
public:
    Field(std::string* name, int type);
    std::string* getName();
    int getType();
    bool isCompatibleType(int type, std::string* lexema);

    std::string getNameType();
    ~Field();
};


#endif //CONTACTS_MANAGER_FIELD_H
