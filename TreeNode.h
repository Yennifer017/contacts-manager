//
// Created by yennifer on 3/24/24.
//

#ifndef CONTACTS_MANAGER_TREENODE_H
#define CONTACTS_MANAGER_TREENODE_H
#include <string>

template <class T>
class TreeNode {
private:
    int weight;
    TreeNode* right;
    TreeNode* left;
    TreeNode* father;
    std::string* key;
    T* content;

public:
    /*CONSTRUCTOR*/
    TreeNode(std::string* key, T* content){
        weight = 1;
        right = nullptr;
        left = nullptr;
        father = nullptr;
        this->key = key;
        this->content = content;
    }

    /*IMPORTANT METHODS*/
    bool isLeaf(){
        return this->right == nullptr && this->left == nullptr;
    }
    int getInclinationWeight(){
        int rightWeight = right == nullptr ? 0 : right->weight;
        int leftWight = left == nullptr ? 0 : left->weight;
        return rightWeight - leftWight;
    }
    bool isBalanced(){
        int diference = this->getInclinationWeight();
        return diference == 0 || diference == 1 || diference == -1;
    }
    bool isRightFromFather(){
        if(father != nullptr){
            return father->getRight() == this;
        }else{
            return false;
        }
    }

    void adjustWeight(){
        int rightWeight = right == nullptr ? 0 : right->weight;
        int leftWight = left == nullptr ? 0 : left->weight;
        int mayor =  rightWeight > leftWight?  rightWeight : leftWight;
        this->weight = 1+mayor;
    }

    /*GETTERS*/
    TreeNode* getRight(){
        return this->right;
    }
    TreeNode* getLeft(){
        return this->left;
    }
    TreeNode* getFather(){
        return this->father;
    }
    std::string* getKey(){
        return this->key;
    }
    T* getContent(){
        return this->content;
    }

    /*SETTERS*/
    void setFather(TreeNode* &_father){
        this->father = _father;
    }
    void setRight(TreeNode* &_right){
        this->right = _right;
    }
    void setLeft(TreeNode* &_left){
        this->left = _left;
    }
    void emptyRightReference(){
        this->right = nullptr;
    }
    void emptyLeftReference(){
        this->left = nullptr;
    }
    void emptyFatherReference(){
        this->father = nullptr;
    }
    ~TreeNode(){};
};


#endif //CONTACTS_MANAGER_TREENODE_H
