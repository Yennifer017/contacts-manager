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

void Exporter::createDirectory(std::string* const name, std::string* const path) {
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
        }
    }
}

void Exporter::createDoc(std::string *content, std::string *name, std::string *path, std::string *extension) {
    // Crear un archivo de texto dentro de la carpeta
    string filePath = path->append("/").append(*name).append(*extension);
    cout<<filePath<<endl;
    ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << *content << endl;
        outputFile.close();
    } else {
        throw std::runtime_error("No se pudo crear correctamente el archivo");
    }
}

