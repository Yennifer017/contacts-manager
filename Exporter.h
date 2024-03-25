//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_EXPORTER_H
#define CONTACTS_MANAGER_EXPORTER_H

#include <iostream>
#include<string>
#include <fstream>
#include <filesystem>

class Exporter {
public:
    static std::string* CURRENT_FOLDER;
    static std::string* TXT_EXTENSION;
    static std::string* GRAPHVIZ_EXTENSION;

    void createDirectory(std::string* name, std::string* path);
    void createDoc(std::string* content, std::string* name, std::string* path, std::string* extension);

};


#endif //CONTACTS_MANAGER_EXPORTER_H
