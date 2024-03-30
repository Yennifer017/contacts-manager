//
// Created by yennifer on 3/26/24.
//

#include <chrono>
#include "Reportero.h"

Reportero::Reportero(HashMap<Group> *&groups) {
    this->groups = groups;
    this->logReport = "";
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

                reporte += currentGroupCont->getContent()->getFieldsAndTypes();

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
        reporte += "--Total de grupos:" + std::to_string(groups->getTotalElements()) + "\n";
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

std::string Reportero::getCurrentTime() {
    // Obtenemos el timepoint actual del reloj del sistema
    auto now = std::chrono::system_clock::now();
    // Convertimos el timepoint a un tiempo (std::time_t)
    std::time_t current_time = std::chrono::system_clock::to_time_t(now);
    // Convertimos el tiempo a una representación legible
    return std::asctime(std::localtime(&current_time));
}
void Reportero::addLogAction(std::string action) {
    std::string logTime = getCurrentTime(); // Convertir el tiempo a std::string
    this->logReport += action +  " -- " + logTime;
}

std::string Reportero::getLogInformation() {
    return "LOGS DEL SISTEMA \n" + (this->logReport.empty() ? "__sin informacion para mostrar__" : this->logReport);
}

void Reportero::addLogFindAction(std::string *nameGroup, std::string *nameField, std::string *searchingFor) {
    std::string logTime = getCurrentTime(); // Convertir el tiempo a std::string
    std::string registro = "Busqueda de <" + *searchingFor + "> realizada en el grupo <" + *nameGroup;
    registro += ">, campo <" + *nameField + ">";
    this->logReport += registro + " -- " + logTime;
}


