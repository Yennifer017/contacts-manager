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
    std::string logReport;
    std::string getCurrentTime();
public:
    Reportero(HashMap<Group>* &groups);
    std::string getTotalContactsPerGroup();
    std::string getInformationPerGroup();
    std::string getGlobalInformation();
    std::string getLogInformation();

    void addLogAction(std::string  action);
    void addLogFindAction(std::string* nameGroup, std::string* nameField, std::string* searchingFor);
};


#endif //CONTACTS_MANAGER_REPORTERO_H
