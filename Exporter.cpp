//
// Created by yennifer on 3/24/24.
//

#include "Exporter.h"


#ifdef _WIN32 //para verificar el sistema operativo y que funcione en ambos
#include <direct.h> // Para Windows
    #define mkdir _mkdir
#else
#include <sys/stat.h> // Para sistemas basados en Unix
#endif

using namespace std;
namespace fs = std::filesystem;

//miembros estaticos
std::string* Exporter::CURRENT_FOLDER = new std::string("..");
std::string* Exporter::TXT_EXTENSION = new std::string(".txt");
std::string* Exporter::GRAPHVIZ_EXTENSION = new std::string(".dot");

std::string Exporter::createDirectory(std::string* const name, std::string* const path) {
    string folderName = path->append("/").append(*name);
    if (fs::exists(folderName) && fs::is_directory(folderName)) {
        throw std::invalid_argument("La carpeta ya existe");
    } else {
        #ifdef _WIN32
            int folderCreated = mkdir(folderName.c_str());
        #else
            int folderCreated = mkdir(folderName.c_str(), 0777); // Permisos en sistemas Unix
        #endif
        if (folderCreated != 0) {
            throw std::invalid_argument("Ocurrio un error al crear la carpeta, es posible que ya exista");
        }else{
            return folderName;
        }
    }
}

void Exporter::createDoc(std::string content, std::string name, std::string path, std::string *extension) {
    // Crear un archivo de texto dentro de la carpeta
    string filePath = path + "/" + name + *extension;
    ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << content << endl;
        outputFile.close();
    } else {
        throw std::runtime_error("No se pudo crear correctamente el archivo");
    }
}

void Exporter::exportGroupData(HashContainer<Group>* &group, int fieldNumber) {
    string pathDirectory = createDirectory(group->getKey(), CURRENT_FOLDER);
    std::string* path = new std::string(pathDirectory);
    LinkedList<Field>* fields = group->getContent()->getFields();
    TreeNode<LinkedList<std::string>>* raizTreeNode = group->getContent()->getHashTable()
            ->get(fields->get(fieldNumber)->getContent()->getName())->getContent()->getRaiz();
    exportContactData(raizTreeNode, fields, path);
}

void Exporter::exportContactData(TreeNode<LinkedList<std::string>> *&treeNode, LinkedList<Field> *&fields,
                                 string *&pathFolder) {
    try {
        std::string content = "";

        Node<std::string>* nodeData = treeNode->getContent()->get(0);
        Node<Field>* nodeField = fields->get(0);
        while (nodeData != nullptr && nodeField != nullptr){
            content +=  *nodeField->getContent()->getName();
            content += "=";
            content += *nodeData->getContent();
            content += "\n";
            nodeData = nodeData->getNext();
            nodeField = nodeField->getNext();
        }
        createDoc(content, *treeNode->getKey(), *pathFolder, TXT_EXTENSION);
    }catch (const std::runtime_error& e){
        cout<<"No se pudo crear un archivo de un contacto: "<<*treeNode->getKey()<<std::endl;
    }
    if(treeNode->getLeft() != nullptr){
        TreeNode<LinkedList<std::string>> * newNode = treeNode->getLeft();
        exportContactData(newNode, fields, pathFolder);
    }
    if(treeNode->getRight() != nullptr){
        TreeNode<LinkedList<std::string>> * newNode = treeNode->getRight();
        exportContactData(newNode, fields, pathFolder);
    }
}

std::string Exporter::getFileSeparator() {
#ifdef _WIN32
    return "\\";
#else
    return "/";
#endif
}



