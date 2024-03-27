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
    groups = new HashMap<Group>();
    translator = new Translator(groups);
    reportero = new Reportero(groups);
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
        int option = util->getNaturalNumber(1, 5);
        switch (option) {
            case 1:
                terminal();
                break;
            case 2:
                break;
            case 3:
                reportsMenu();
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
        translator->translate(tokens);

        /*std::cout<<"En la tabla principal de grupos:"<<std::endl;
        groups->showKeys();
        std::cout<<"En la tabla secundaria de cliente:"<<std::endl;
        groups->get(new std::string("clientes"))->getContent()->getHashTable()->showKeys();*/

        util->enterContinue();
    } while (true);

}

void Manager::reportsMenu() {
    bool running = true;
    do {
        util->clearConsole();
        util->printSeparator();
        std::cout<<"Ingresa el numero de reporte que deseas ver\n    1->Cantidad de datos por grupo\n    ";
        std::cout<<"2->Cantidad de datos de todo el sistema\n";
        std::cout<<"    3->Cantidad de contactos por grupo\n    4->Log del sistema\n    5->Salir del menu de reportes"<<std::endl;
        util->printSeparator();
        int option = util->getNaturalNumber(1, 5);
        switch (option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                std::cout<<reportero->getTotalContactsPerGroup()<<std::endl;
                util->enterContinue();
                break;
            case 4:
                break;
            default:
                running = false;
                break;
        }
    } while (running);
}
