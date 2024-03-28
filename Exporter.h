//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_EXPORTER_H
#define CONTACTS_MANAGER_EXPORTER_H

#include <iostream>
#include<string>
#include <fstream>
#include <filesystem>
#include "HashContainer.h"
#include "Group.h"
#include "TreeNode.h"
#include "LinkedList.h"
#include "Node.h"

class Exporter {
private:
    void exportContactData(TreeNode<LinkedList<std::string>>* &treeNode, LinkedList<Field>* &fields,std::string* &pathFolder);
public:
    static std::string* CURRENT_FOLDER;
    static std::string* TXT_EXTENSION;
    static std::string* GRAPHVIZ_EXTENSION;

    std::string createDirectory(std::string* name, std::string* path);
    void createDoc(std::string content, std::string name, std::string path, std::string* extension);

    void exportGroupData(HashContainer<Group>* &group, int fieldNumber);
};


#endif //CONTACTS_MANAGER_EXPORTER_H
