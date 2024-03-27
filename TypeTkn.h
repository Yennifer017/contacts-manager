//
// Created by yennifer on 3/20/24.
//

#ifndef CONTACTS_MANAGER_TYPETKN_H
#define CONTACTS_MANAGER_TYPETKN_H
enum class TypeTkn {
    ADD = 1,
    NEW = 2,
    GROUP = 3,
    FIELDS = 4,
    /*typo de datos para especificar*/
    STRING_NAME = 5,
    INTEGER_NAME = 6,
    DATE_NAME = 7,
    CHAR_NAME = 8,

    CONTACT = 9,
    FIND = 10,
    IN = 11,
    ID = 12,
    /*typo de datos que se pueden tener*/
    ENTERO = 13,
    CADENA = 14,
    CARACTER = 15,
    FECHA = 22,

    IGUAL = 16,
    GUION = 17,
    PARENTESIS_L = 18,
    PARENTESIS_R = 19,
    COMA = 20,
    FIN_INSTRUCCION = 21

};
#endif //CONTACTS_MANAGER_TYPETKN_H
