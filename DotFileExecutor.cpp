//
// Created by yennifer on 3/27/24.
//

#include "DotFileExecutor.h"

void DotFileExecutor::generateImage(std::string code, std::string path, std::string nameFile) {
    std::string temporalFile = *Exporter::CURRENT_FOLDER + Exporter::getFileSeparator() + "graph.dot";
    std::ofstream file(temporalFile); // Crea un archivo DOT
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
    }
    file << code << std::endl; // Comienza la definición del gráfico
    file.close(); // Cierra el archivo

    // Ejecuta Graphviz para generar la imagen del gráfico
    std::string command = "dot -Tpng ";
    command += temporalFile;
    command += " -o ";
    command += path + Exporter::getFileSeparator();
    //command += "../";
    command += nameFile;
    command += ".png";
    const char *commandChar = command.c_str();
    system(commandChar);
    //remove("../graph.dot");
    std::string* temporalFilePath = new std::string(temporalFile);
    remove(reinterpret_cast<const char *>(temporalFilePath));
}
