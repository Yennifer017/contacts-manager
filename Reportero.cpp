//
// Created by yennifer on 3/26/24.
//

#include "Reportero.h"

Reportero::Reportero(HashMap<Group> *&groups) {
    this->groups = groups;
}

std::string Reportero::getTotalContactsPerGroup() {
    std::string reporte = "   # CONTEO DE CONTACTOS POR GRUPO\n\n";
    if(groups->getTotalElements() == 0 ){
        reporte += "__no hay grupos agregados aun__\n";
    }else{
        for (int i = 0; i < groups->getSize(); ++i) {
            HashContainer<Group>* currentGroupCont = groups->get(i);
            if(currentGroupCont != nullptr){
                reporte += "-> Nombre del grupo: ";
                reporte += *currentGroupCont->getKey();
                reporte += 9;
                reporte += 9;
                reporte += "Cant. de contactos: ";
                reporte +=  std::to_string(currentGroupCont->getContent()
                                                   ->getHashTable()->getFirstNonNullData()->getContent()->getTotalElements());
                reporte += "\n";
            }
        }
    }
    return reporte;
}

std::string Reportero::getInformationPerGroup() {
    std::string reporte = "   # CANTIDAD DE DATOS POR GRUPO\n* * * * * * * * * * * * * * * * * *\n\n";
    if(groups->getTotalElements() == 0 ){
        reporte += "__no hay grupos agregados aun__\n";
    }else{
        for (int i = 0; i < groups->getSize(); ++i) {
            HashContainer<Group>* currentGroupCont = groups->get(i);
            if(currentGroupCont != nullptr){
                reporte += "  ->Nombre del grupo: ";
                reporte += *currentGroupCont->getKey();
                reporte += "\n    Total de campos de datos: ";
                reporte += std::to_string(currentGroupCont->getContent()->getFields()->getSize());
                reporte += "\n          ";

                int index = 1;
                Node<Field>* fieldNode = currentGroupCont->getContent()->getFields()->get(0);
                while (fieldNode != nullptr){
                    reporte += std::to_string(index);
                    reporte += "=[" + *fieldNode->getContent()->getName() + "] ";
                    fieldNode = fieldNode->getNext();
                    index++;
                }

                reporte += "\n    Total de datos (todos los campos de contactos en los arboles): ";
                reporte +=  std::to_string(currentGroupCont->getContent()
                        ->getHashTable()->getFirstNonNullData()->getContent()->getTotalElements()
                        * currentGroupCont->getContent()->getFields()->getSize());
                reporte += "\n\n * * * * * * * * * * * * * * * * * *\n";
            }
        }
    }

    return reporte;
}

std::string Reportero::getGlobalInformation() {
    std::string reporte = "   # DATOS DE TODO EL SISTEMA\n\n";
    if(groups->getTotalElements() == 0 ){
        reporte += "__El sistema aun no cuenta con informacion__\n";
    }else{
        reporte += "--Total de grupos:" + std::to_string(groups->getSize()) + "\n";
        int totalData = 0;
        for (int i = 0; i < groups->getSize(); ++i) {
            HashContainer<Group>* currentGroupCont = groups->get(i);
            if(currentGroupCont != nullptr){
                //sumando la cantidad de datos de los grupos
                totalData += currentGroupCont->getContent()->getHashTable()->getFirstNonNullData()->getContent()->getTotalElements()
                        * currentGroupCont->getContent()->getFields()->getSize();
            }
        }
        reporte += "--Total de datos (en todos los grupos): " + std::to_string(totalData) + "\n\n";
        reporte += "**Total de datos en el sistema: " + std::to_string(groups->getSize() + totalData) + "\n";
    }
    return reporte;
}
