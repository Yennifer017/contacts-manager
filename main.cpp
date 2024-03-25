#include <iostream>
#include "Lexer.h"
#include "LinkedList.h"
#include "Token.h"
#include "HashMap.h"
#include "Exporter.h"
#include "Manager.h"
#include "TreeGraficator.h"
#include "AVLtree.h"

int main() {
    /*Lexer* lexer = new Lexer();
    std::string* text = new std::string("ADD NEW-GROUP clientes FIELDS (nombre STRING, apellido STRING, celular INTEGER);");
    LinkedList<Token>* tokens = lexer->analizar(text);
    int index = 0;
    Node<Token> *current = tokens->get(index);
    while (current != nullptr){
        std::cout<<*current->getContent()->getLexema()<<"-type:";
        std::cout<<current->getContent()->getType()<<std::endl;
        current = current->getNext();
    }*/


    /*HashMap<std::string> *map = new HashMap<std::string>();
    map->insert(new std::string("adios"), new std::string("contenidoo 4"));
    map->insert(new std::string("hola"), new std::string("contenidoo 1"));
    map->insert(new std::string("clave1"), new std::string("contenidoo 2"));
    map->insert(new std::string("claveeee"), new std::string("contenidoo 3"));
    map->showKeys();

    //map->showKeys();
    std::cout<<*map->get(new std::string("hola"))->getContent()<<std::endl;*/

    /*Exporter* exporter = new Exporter();
    exporter->createDirectory(new std::string("miCarpeta"), Exporter::CURRENT_FOLDER);
    exporter->createDoc(new std::string("contenido"), new std::string("miArchivo"), Exporter::CURRENT_FOLDER, Exporter::TXT_EXTENSION);
    */

    /*Manager* manager = new Manager();
    manager->showMenu();*/




    AVLtree< Node<std::string> >* tree = new AVLtree< Node<std::string> >();
    std::string* code1 = new std::string("moltes");
    std::string* code2 = new std::string("articuno");
    std::string* code3 = new std::string("zapdos");
    std::string* code4 = new std::string("dedalo");
    Node<std::string>* node1 = new Node<std::string>(new std::string("hola"));
    Node<std::string>* node2 = new Node<std::string>(new std::string("adios"));
    Node<std::string>* node3 = new Node<std::string>(new std::string("bye"));
    Node<std::string>* node4 = new Node<std::string>(new std::string("hi"));

    tree->insert(code1, node1);
    tree->insert(code2, node2);
    tree->insert(code3, node3);
    tree->insert(code4, node4);

    TreeGraficator<Node<std::string>>* graph = new TreeGraficator<Node<std::string>> ();
    graph->setNameTree(new std::string("arbol1"));
    graph->graficateTree(tree, "grafico");



    return 0;
}
