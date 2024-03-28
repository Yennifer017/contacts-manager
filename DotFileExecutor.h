//
// Created by yennifer on 3/27/24.
//

#ifndef CONTACTS_MANAGER_DOTFILEEXECUTOR_H
#define CONTACTS_MANAGER_DOTFILEEXECUTOR_H
#include <string>
#include <fstream>
#include <iostream>
#include "Exporter.h"

class DotFileExecutor {
public:
    void generateImage(std::string code, std::string path, std::string nameFile);
};


#endif //CONTACTS_MANAGER_DOTFILEEXECUTOR_H
