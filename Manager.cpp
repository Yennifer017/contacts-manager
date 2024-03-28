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
    reportero = new Reportero(groups);
    translator = new Translator(groups, reportero);
    exporter = new Exporter();
    grapher = new Grapher();
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
                generateGraphicsMenu();
                break;
            case 3:
                reportsMenu();
                break;
            case 4:
                exportationMenu();
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
                std::cout<<reportero->getInformationPerGroup()<<std::endl;
                break;
            case 2:
                std::cout<<reportero->getGlobalInformation()<<std::endl;
                break;
            case 3:
                std::cout<<reportero->getTotalContactsPerGroup()<<std::endl;
                break;
            case 4:
                std::cout<<reportero->getLogInformation()<<std::endl;
                break;
            default:
                running = false;
                break;
        }
        if(running){
            util->enterContinue();
        }
    } while (running);
}

void Manager::exportationMenu() {
    do {
        util->clearConsole();
        util->printSeparator();
        std::cout << " MENU DE EXPORTACION " << std::endl;
        util->printSeparator();
        std::cout << "Grupos existentes:" << std::endl;
        groups->showExistentKeys();
        std::cout << "\nEscribe el nombre del grupo a exportar:" << std::endl;
        std::string *nameGroup = util->getLectura();
        try {
            HashContainer<Group> *containerGroup = this->groups->get(nameGroup);
            Group *group = containerGroup->getContent();
            std::cout << "\nIngresa el numero de campo para obtener el nombre de los archivos a exportar:" << std::endl;
            std::cout << group->getFieldsAndTypes() << std::endl;
            int fieldDefineName = util->getNaturalNumber(1, group->getFields()->getSize());
            fieldDefineName--;
            exporter->exportGroupData(containerGroup, fieldDefineName);
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        }
        util->enterContinue();
        std::cout<<"Deseas realizar otra exportacion?   [1-Si / 2-No]"<<std::endl;
        int continueVal = util->getNaturalNumber(1, 2);
        if(continueVal == 2 ){
            break;
        }
    } while (true);
}

void Manager::generateGraphicsMenu() {
    bool running = true;
    do{
        util->clearConsole();
        util->printSeparator();
        std::cout<<"MENU DE GRAFICOS"<<std::endl;
        util->printSeparator();
        std::cout<<"Ingresa que tipo de grafico quieres exportar:"<<std::endl;
        std::cout<<"    1->De toda la estructura\n    2->De un grupo\n    3->De una estructura especifica"<<std::endl;
        std::cout<<"    4->Salir"<<std::endl;
        int option = util->getNaturalNumber(1, 4);
        switch (option) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                specificGraphMenu();
                break;
            default:
                running = false;
                break;
        }
    }while (running);
}

void Manager::specificGraphMenu() {
    util->printSeparator();
    std::cout<<"Ingresa que estructura deseas graficar:"<<std::endl;
    std::cout<<"    1-HashTable de los grupos\n    2->HashTable de campos de un grupo especifico"<<std::endl;
    std::cout<<"    3->ArbolAVL de un campo de un grupo\n    4->Salir"<<std::endl;
    int option = util->getNaturalNumber(1,4);
    switch (option) {
        case 1:
            //grapher->getGroupTableGrapher()->graficateHashTable("GROUPS", groups, true, "GROUPS_GRAPH");
            break;
        case 2:
            break;
        case 3:
            treeGraphMenu();
            break;
        default: //salir de este menu
            break;
    }
}

void Manager::treeGraphMenu() {
    std::cout << "Grupos existentes:" << std::endl;
    groups->showExistentKeys();
    std::cout << "\nEscribe el nombre del grupo a exportar:" << std::endl;
    std::string *nameGroup = util->getLectura();
    try {
        HashContainer<Group> *containerGroup = this->groups->get(nameGroup);
        Group *group = containerGroup->getContent();
        std::cout << "\nIngresa el numero de campo para obtener el arbol AVL:" << std::endl;
        std::cout << group->getFieldsAndTypes() << std::endl;
        int fieldDefineName = util->getNaturalNumber(1, group->getFields()->getSize());
        fieldDefineName--;
        grapher->getTreeGrapher()->graficateTree(group->getHashTable()->get(
                group->getFields()->get(fieldDefineName)->getContent()->getName())->getContent(), "ARBOL_");
    } catch (const std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}
