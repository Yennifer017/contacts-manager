//
// Created by yennifer on 3/26/24.
//

#ifndef CONTACTS_MANAGER_REPORTERO_H
#define CONTACTS_MANAGER_REPORTERO_H

#include <string>
#include "Group.h"
#include "HashMap.h"

class Reportero {
private:
    HashMap<Group> *groups;
public:
    Reportero(HashMap<Group>* &groups);
    std::string getTotalContactsPerGroup();
    std::string getInformationPerGroup();
    std::string getGlobalInformation();
};


#endif //CONTACTS_MANAGER_REPORTERO_H
