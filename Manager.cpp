//
// Created by yennifer on 3/24/24.
//

#include <string>
#include <iostream>
#include <algorithm>
#include "Manager.h"

Manager::Manager() {
    util = new Util();
    lexer = new Lexer();
}

void Manager::showMenu() {
    bool running = true;
    do {
        util->clearConsole();
        util->printSeparator();
        std::cout<<"**    CONTACTS - MANAGER   **"<<std::endl;
        util->printSeparator();
        std::cout<<"Que deseas hacer?\n    1->Ir a la linea de comandos\n    2->Generar graficas\n";
        std::cout<<"    3->Ver Reportes\n    4->Exportacion de datos\n    5->Salir del sistema"<<std::endl;
        int option = util->getNaturalNumber(1, 4);
        switch (option) {
            case 1:
                terminal();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                running = false;
                break;
        }
        util->printSeparator();
    } while (running);
}

void Manager::terminal() {
    do {
        util->clearConsole();
        std::cout<<"A continuacion ingresa el/los comando(s)\n[0 - para salir]: "<<std::endl;
        std::string* instructions = util->getLectura();
        if(instructions->compare("0") == 0){
            break;
        }
        LinkedList<Token>* tokens = lexer->analizar(instructions);

        util->enterContinue();
    } while (true);

}
