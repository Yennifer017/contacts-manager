//
// Created by yennifer on 3/21/24.
//

#include "Util.h"
#include <iostream>
#include <limits>

std::string *Util::getLectura() {
    std::string lectura;
    printGetter();
    std::cin.clear();
    std::cin.ignore();
    std::getline(std::cin, lectura); // Leer toda la línea
    return new std::string(lectura);
}

void Util::enterContinue() {
    std::cout<<"Ingrese cualquier letra/numero para continuar\n";
    std::string lectura;
    std::cin.clear();
    std::cin >> lectura;
    lectura.clear();
}

void Util::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    // ANSI Escape Code for clearing the screen
    std::cout << "\033[2J\033[1;1H"<<std::endl;
#endif
}

int Util::getNumber() {
    do{
        try {
            std::string lectura;
            printGetter();
            std::cin >> lectura;
            int number = std::stoi(lectura);
            return number;
        }
        catch (std::invalid_argument const &e) {
            std::cout << "Numero invalido, intentalo otra vez: " <<std::endl;
        }
        catch (std::out_of_range const &e) {
            std::cout << "Integer overflow error, ingresa un numero mas pequeno: ";
        }
    } while (true);
}

int Util::getNaturalNumber(int min, int max) {
    if(min>max){
        throw std::invalid_argument("Error: Incoherencia de datos para numeros");
    }
    do {
        int number = getNumber();
        if(number>=min && number<=max){
            return number;
        }else{
            printf("Numbero invalido, debe estar entre %d y %d: ", min, max);
        }
    } while (true);
}

void Util::printSeparator() {
    std::cout<<"-----------------------------------------------------------"<<std::endl;
}

void Util::printGetter() {
    std::cout<<"      >>";
}
