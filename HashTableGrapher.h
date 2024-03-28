//
// Created by yennifer on 3/27/24.
//

#ifndef CONTACTS_MANAGER_HASHTABLEGRAPHER_H
#define CONTACTS_MANAGER_HASHTABLEGRAPHER_H
#include "HashMap.h"
#include "HashContainer.h"
#include "DotFileExecutor.h"

template <class T>
class HashTableGrapher {
private:
    std::string *EMPTY = new std::string("__EMPTY__");
    int numberNode;
    std::string* nameHashTable;
    DotFileExecutor* dotFileExecutor;

    std::string getConnectNodeCode(int father, int child){
        return *nameHashTable + std::to_string(father) + "->" + *nameHashTable + std::to_string(child) + ";\n";
    }

    std::string createGraphNode(std::string* label){
        std::string code = *nameHashTable + std::to_string(numberNode);
        code += "[label=\"" + *label + "\"];\n";
        return code;
    };


public:
    HashTableGrapher(){
        numberNode = 0;
        nameHashTable = new std::string("");
        dotFileExecutor = new DotFileExecutor();
    }

    std::string getCodeGraphTable(std::string* nameTable, HashMap<T>* &hashMap, bool includeEmptyPositions){
        numberNode = 0;
        std::string code = "";
        code  += createGraphNode(nameTable);
        numberNode++;
        for (int i = 0; i < hashMap->getSize(); ++i) {
            HashContainer<T>* hashContainer = hashMap->get(i);
            if(hashContainer == nullptr && includeEmptyPositions){
                code += createGraphNode(EMPTY);
                code += getConnectNodeCode(0, numberNode);
                numberNode++;
            }else if(hashContainer != nullptr){
                code += createGraphNode(hashContainer->getKey());
                code += getConnectNodeCode(0, numberNode);
                numberNode++;
            }
        }
        return code;
    }

    void graficateHashTable(std::string* nameTable, HashMap<T>* &hashMap, bool includeEmptyPositions, std::string nameGraph){
        numberNode = 0;
        std::string code = "digraph hashTable{";
        code += getCodeGraphTable(nameTable, hashMap, includeEmptyPositions);
        code += "}";
        dotFileExecutor->generateImage(code, *Exporter::CURRENT_FOLDER, nameGraph);
    };


    void setNameHashTable(std::string* nameHashTable){
        this->nameHashTable = nameHashTable;
    }

    std::string* getNameHashTable(){
        return this->nameHashTable;
    }

};


#endif //CONTACTS_MANAGER_HASHTABLEGRAPHER_H
