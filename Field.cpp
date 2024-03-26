//
// Created by yennifer on 3/25/24.
//

#include "Field.h"

std::string *Field::getName() {
    return this->name;
}

int Field::getType() {
    return this->type;
}

Field::Field(std::string* name, int type) {
    this->name = name;
    this->type = type;
}
