//
// Created by yennifer on 3/25/24.
//

#ifndef CONTACTS_MANAGER_TREEGRAFICATOR_H
#define CONTACTS_MANAGER_TREEGRAFICATOR_H

#include "AVLtree.h"
#include "LinkedList.h"
#include "Node.h"
#include "TreeNode.h"
#include "Exporter.h"
#include "DotFileExecutor.h"

template <class T>
class TreeGraficator {
private:
    int numberNode;
    std::string* nameTree;
    std::string* RED_COLOR = new std::string("red"), * BLUE_COLOR = new std::string("blue"), * GREEN_COLOR = new std::string("green");

    Exporter* exporter;
    DotFileExecutor* dotFileExecutor;

    std::string createGraphNode(TreeNode<T>* node, std::string* &color){
        std::string code = *nameTree;
        code += std::to_string(numberNode);
        code += "[label=\"";
        code += *node->getKey();
        code += "\"";
        if(color != nullptr){
            code += ", color=\"";
            code += *color;
            code += "\"";
        }
        code += "];\n";
        return code;
    };

    std::string codeGraphTreeNode(TreeNode<T>* node, bool hasFather, int numberFather, std::string* &color){
        int currentNode = numberNode;
        std::string code = createGraphNode(node, color);
        if(hasFather){
            code += *nameTree;
            code += std::to_string(numberFather);
            code += "->";
            code += *nameTree;
            code += std::to_string(currentNode);
            code += ";\n";
        }
        if(node->getLeft() != nullptr){
            numberNode++;
            code += codeGraphTreeNode(node->getLeft(), true, currentNode, BLUE_COLOR);
        }
        if(node->getRight() != nullptr){
            numberNode++;
            code += codeGraphTreeNode(node->getRight(), true, currentNode, RED_COLOR);
        }
        return code;
    };
public:
    TreeGraficator(){
        exporter = new Exporter();
        numberNode = 0;
        nameTree = new std::string("");
        dotFileExecutor = new DotFileExecutor();
    };
    void graficateTree(AVLtree<T>* tree, std::string nameGraph){
        numberNode = 0;
        std::string code = "digraph tree{";
        if(!tree->isEmpty()){
            TreeNode<T>* raiz = tree->getRaiz();
            code += codeGraphTreeNode(raiz, false, 0, GREEN_COLOR);
        }
        code += "}";
        dotFileExecutor->generateImage(code, *Exporter::CURRENT_FOLDER, nameGraph);
    };

    std::string getCodeForTree(AVLtree<T>* tree){
        this->numberNode = 0;
        if(!tree->isEmpty()){
            TreeNode<T>* raiz = tree->getRaiz();
            return codeGraphTreeNode(raiz, false, 0, GREEN_COLOR);
        }
        return "";
    }

    void setNameTree(std::string* nameTree){
        this->nameTree = nameTree;
    }

    std::string* getNameTree(){
        return this->nameTree;
    }

    ~TreeGraficator(){};
};


#endif //CONTACTS_MANAGER_TREEGRAFICATOR_H
