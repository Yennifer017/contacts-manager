//
// Created by yennifer on 3/27/24.
//

#include "Grapher.h"

Grapher::Grapher() {
    dotFileExecutor = new DotFileExecutor();
    groupTableGrapher = new HashTableGrapher<Group>();
    fieldTableGrapher = new HashTableGrapher<AVLtree<LinkedList<std::string>>>();
    treeGrapher = new TreeGraficator<LinkedList<std::string>>();

}

HashTableGrapher<Group> *Grapher::getGroupTableGrapher() {
    return this->groupTableGrapher;
}

HashTableGrapher<AVLtree<LinkedList<std::string>>> *Grapher::getFieldTableGrapher() {
    return this->fieldTableGrapher;
}

TreeGraficator<LinkedList<std::string>> *Grapher::getTreeGrapher() {
    return this->treeGrapher;
}

std::string Grapher::graphGroup(std::string *nameGroup, Group *group) {
    std::string code = "digraph group{";
    HashMap<AVLtree<LinkedList<std::string>>>* hashMapFields = group->getHashTable();
    code += getCodeOneGroup(nameGroup, hashMapFields);
    code += "}";
    std::string nameGraph = *nameGroup + "_compleate_struct";
    dotFileExecutor->generateImage(code, *Exporter::CURRENT_FOLDER, nameGraph);
    return nameGraph;
}

std::string Grapher::graphAll(std::string *namePrincipalGroup, HashMap<Group> *&groups) {
    std::string code = "digraph allData{";
    code += getCodeForAll(namePrincipalGroup,groups);
    code += "}";
    std::string nameGraph = "all_system_data";
    dotFileExecutor->generateImage(code, *Exporter::CURRENT_FOLDER, nameGraph);
    return nameGraph;
}

std::string Grapher::getConnectCode(std::string *nameFather, std::string *nameChild) {
    return *nameFather + "->" + *nameChild + ";\n";
}

std::string Grapher::getCodeOneGroup(std::string *nameGroup, HashMap<AVLtree<LinkedList<std::string>>>* &hashMapFields) {
    std::string code = "";
    fieldTableGrapher->setNameHashTable(nameGroup);
    code += fieldTableGrapher->getCodeGraphTable(nameGroup, hashMapFields, true);
    for (int i = 1; i <= hashMapFields->getSize(); ++i) {
        HashContainer<AVLtree<LinkedList<std::string>>>* hashContainer = hashMapFields->get(i - 1);
        if(hashContainer != nullptr && !hashContainer->getContent()->isEmpty()){
            std::string nameNodesTree = *nameGroup + "_" + *hashContainer->getKey() + "_";
            treeGrapher->setNameTree(new std::string(nameNodesTree));
            code += treeGrapher->getCodeForTree(hashContainer->getContent());

            std::string* fieldDotName = new std::string(*fieldTableGrapher->getNameHashTable() + std::to_string(i));
            std::string* treeDotName = new std::string(*treeGrapher->getNameTree() + std::to_string(0));
            code += getConnectCode(fieldDotName, treeDotName);
        } //TODO: agregar que el arbol esta vacio
    };
    return code;
}

std::string Grapher::getCodeForAll(std::string *nameGroup, HashMap<Group> *&groups) {
    std::string code = "";
    groupTableGrapher->setNameHashTable(nameGroup);
    code += groupTableGrapher->getCodeGraphTable(nameGroup, groups, true);
    for (int i = 1; i <= groups->getSize(); ++i) {
        auto *hashContainer = groups->get(i-1);
        if(hashContainer != nullptr){
            auto *fieldsHashTable = hashContainer->getContent()->getHashTable();
            code += getCodeOneGroup(new std::string("fields_" + *hashContainer->getKey()), fieldsHashTable);

            std::string* groupDotName = new std::string(*groupTableGrapher->getNameHashTable() + std::to_string(i));
            std::string* fieldTableName = new std::string(*fieldTableGrapher->getNameHashTable() + std::to_string(0));
            code += getConnectCode(groupDotName, fieldTableName);
        }
    }
    return code;
}

std::string Grapher::createNode(std::string name, std::string label) {
    std::string code = name;
    code += "[label=\"";
    code += label;
    code += "\"";
    code += "];\n";
    return code;
}
