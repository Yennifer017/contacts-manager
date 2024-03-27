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
