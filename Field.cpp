//
// Created by yennifer on 3/25/24.
//

#include "Field.h"
#include "TypeTkn.h"

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

bool Field::isCompatibleType(int type) {
    switch (this->type) {
        case static_cast<int>(TypeTkn::STRING_NAME):
            return type == static_cast<int>(TypeTkn::CADENA) || type == static_cast<int>(TypeTkn::ID);
        case static_cast<int>(TypeTkn::INTEGER_NAME):
            return type == static_cast<int>(TypeTkn::ENTERO);
        case static_cast<int>(TypeTkn::CHAR_NAME):
            return type == static_cast<int>(TypeTkn::CARACTER);
        case static_cast<int>(TypeTkn::DATE_NAME):
            return type == static_cast<int>(TypeTkn::FECHA);
        default:
            return false;
    }
}

std::string Field::getNameType() {
    switch (this->type) {
        case static_cast<int>(TypeTkn::STRING_NAME):
            return "STRING";
        case static_cast<int>(TypeTkn::INTEGER_NAME):
            return "INTEGER";
        case static_cast<int>(TypeTkn::CHAR_NAME):
            return "CHAR";
        case static_cast<int>(TypeTkn::DATE_NAME):
            return "DATE";
        default:
            return "UNKNOWN";
    }
}
