//
// Created by yennifer on 3/25/24.
//

#include "Translator.h"

Translator::Translator(HashMap<Group> *&groups, Reportero* &_reportero) {
    this->groups = groups;
    this->reportero = _reportero;
    this->searcher = new Searcher<LinkedList<std::string>>();
}

void Translator::translate(LinkedList<Token>* &tokens) {
    Node<Token>* currentNode = tokens->get(0);
    std::cout<<std::endl;
    while (currentNode != nullptr){
        switch (currentNode->getContent()->getType()) {
            case static_cast<int>(TypeTkn::ADD) :
                translateAddInstructions(tokens, currentNode);
                break;
            case static_cast<int>(TypeTkn::FIND) :
                std::cout<<translateFindStm(tokens, currentNode)<<std::endl;
                break;
            default:
                //pasar en caso se quede suspendido
                break;
        }
        currentNode = currentNode->getNext();
    }
}

std::string Translator::translateAddGroupStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
    LinkedList<Field>* fields = new LinkedList<Field>;
    current = current->getNext()->getNext()->getNext()->getNext(); //para apuntar al nombre del grupo
    std::string* nameGroup = current->getContent()->getLexema();
    current = current->getNext()->getNext()->getNext(); //para apuntar al primer campo de datos
    while (current->getContent()->getType() != static_cast<int>(TypeTkn::PARENTESIS_R)){
        if(current->getContent()->getType() != static_cast<int>(TypeTkn::COMA)){
            Field* field = new Field(current->getContent()->getLexema(), current->getNext()->getContent()->getType());
            fields->insertLast(field);
            current = current->getNext()->getNext(); //para irnos o a la coma o al parentesis
        }else{
            current = current->getNext();
        }
    }
    current = current->getNext(); //para parar en el punto y coma
    Group *group;
    try {
         group = new Group(fields);
    }catch (const std::invalid_argument& e) {
        throw std::invalid_argument("Se encontro un nombre de un campo repetido en <" + *nameGroup + "> No se pudo insertar");
    }
    try {
        groups->insert(nameGroup, group);
    }catch (const std::invalid_argument& e) {
        delete(group);
        throw std::invalid_argument("El grupo <" + *nameGroup + "> ya existe, no se pudo insertar");
    }
    std::string result = "Grupo <" + *nameGroup + "> agregado exitosamente";
    return result;
}

std::string Translator::translateAddContactStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
    current = current->getNext()->getNext()->getNext(); //para apuntar al nombre del grupo
    std::string* nameGroup = current->getContent()->getLexema();
    HashContainer<Group>* hashContGroup = groups->get(nameGroup);
    Group* currentGroup = hashContGroup->getContent();
    LinkedList<Token>* data = new LinkedList<Token>();
    current = current->getNext()->getNext()->getNext(); //para apuntar al primer dato
    while (current->getContent()->getType() != static_cast<int>(TypeTkn::PARENTESIS_R) ){
        if(current->getContent()->getType() != static_cast<int>(TypeTkn::COMA)){
            if(current->getContent()->getType() == static_cast<int>(TypeTkn::ENTERO) //save a date
                && current->getNext()->getContent()->getType() == static_cast<int>(TypeTkn::GUION)){
                std::string* lexema = new std::string("");
                while (current->getContent()->getType() == static_cast<int>(TypeTkn::ENTERO)
                    || current->getContent()->getType() == static_cast<int>(TypeTkn::GUION)){
                    lexema->append(*current->getContent()->getLexema());
                    current = current->getNext();
                }
                Token* token = new Token(lexema, static_cast<int>(TypeTkn::FECHA));
                data->insertLast(token);
            }else{ //save other data
                Node<Token>* tokenNodeCurrent = current;
                current = current->getNext();
                data->insertLast(tokenNodeCurrent, true);
            }
        }else{
            current = current->getNext();
        }
    }
    LinkedList<std::string>* contactInformation = convertData(currentGroup->getFields(), data);
    HashMap< AVLtree< LinkedList<std::string> > > *tableIformation = currentGroup->getHashTable();
    insertDataInTree(tableIformation, contactInformation, currentGroup->getFields());
    current = current->getNext(); //para parar en el punto y coma
    return "Contacto agregado exitosamente en <" + *nameGroup + ">";
}

void Translator::translateAddInstructions(LinkedList<Token>* &tokens, Node<Token>* &currentNode) {
    switch (currentNode->getNext()->getContent()->getType()) {
        case static_cast<int>(TypeTkn::NEW):
            try {
                std::string result = translateAddGroupStm(tokens, currentNode);
                reportero->addLogAction(result);
                std::cout<<result<<std::endl;
            }catch (const std::invalid_argument& e) {
                std::cout<<e.what()<<std::endl;
            }
            break;
        case static_cast<int>(TypeTkn::CONTACT):
            try {
                std::string result = translateAddContactStm(tokens, currentNode);
                reportero->addLogAction(result);
                std::cout<<result<<std::endl;
            } catch (const std::invalid_argument& e) {
                std::cout<<e.what()<<std::endl;
            }
            break;
        default:
            throw std::invalid_argument("Errores sintacticos encontrados");
    }
}

LinkedList<std::string> *Translator::convertData(LinkedList<Field> *fields, LinkedList<Token> *&data) {
    LinkedList<std::string>* dataConverted = new LinkedList<std::string>();
    if(data->getSize() != fields->getSize()){
        throw std::invalid_argument("La cantidad de datos no concuerda");
    }
    Node<Field>* currentField = fields->get(0);
    Node<Token>* currenTkn = data->get(0);
    while (currentField != nullptr){
        if(!currentField->getContent()->isCompatibleType(currenTkn->getContent()->getType(), currenTkn->getContent()->getLexema())){
            std::string error = "El dato de la instruccion <";
            error += *currenTkn->getContent()->getLexema();
            error += "> no concuerda en tipo";
            throw std::invalid_argument(error);
        }
        dataConverted->insertLast(currenTkn->getContent()->getLexema());
        currenTkn = currenTkn->getNext();
        currentField = currentField->getNext();
    }
    return dataConverted;
}

void Translator::insertDataInTree(HashMap<AVLtree<LinkedList<std::string>>>* &tableGroup, LinkedList<std::string>* &data,
                                  LinkedList<Field>* fields) {
    Node<Field>* currentField = fields->get(0);
    Node<std::string>* dataNode = data->get(0);
    while (currentField != nullptr){
        AVLtree<LinkedList<std::string>> *tree = tableGroup->get(currentField->getContent()->getName())->getContent();
        std::string* keyTree = dataNode->getContent();
        tree->insert(keyTree, data);
        dataNode = dataNode->getNext();
        currentField = currentField->getNext();
    }
}

std::string Translator::translateFindStm(LinkedList<Token> *&tokens, Node<Token> *&current) {
    std::string result;
    current = current->getNext()->getNext()->getNext(); //apuntar a nombre del grupo
    try {
        std::string* nameGroup = current->getContent()->getLexema();
        Group* group = groups->get(nameGroup)->getContent();

        current = current->getNext()->getNext()->getNext()->getNext(); //apuntar a nombre del campo a buscar
        std::string* nameField = current->getContent()->getLexema();
        AVLtree<LinkedList<std::string>>* tree = group->getHashTable()->get(nameField)->getContent();

        current = current->getNext()->getNext(); //para apuntar al nombre del dato a buscar
        std::string* searchingFor = current->getContent()->getLexema();
        LinkedList<Field>* fields = group->getFields();
        auto* raiz = tree->getRaiz();
        if(!tree->isEmpty()){
            result += findInformation(searchingFor, fields, raiz);
        }
        reportero->addLogFindAction(nameGroup, nameField, searchingFor);
    }catch (const std::invalid_argument& e){
        result += e.what();
    }
    result = result.empty() ? "__NO HAY INFORMACION PARA MOSTRAR__\n" : result;
    return " --------------------------------------------\nResultados de la busqueda:\n"
            +result + "\n --------------------------------------------\n";
}

std::string Translator::findInformation(std::string* key, LinkedList<Field>* &fieldsList, TreeNode<LinkedList<std::string>>* treeNode) {
    std::string information = "";
    try {
        TreeNode<LinkedList<std::string>> *treeNodeFind = searcher->find(key, treeNode);

        //agregar la informacion del contacto
        Node<std::string>* currentNodeInf = treeNodeFind->getContent()->get(0);
        Node<Field>* currentField = fieldsList->get(0);
        while (currentNodeInf != nullptr && currentField != nullptr){
            information += *currentField->getContent()->getName() + " = " + *currentNodeInf->getContent();
            if(currentNodeInf->getNext() != nullptr){
                information += 9;
            }
            currentNodeInf = currentNodeInf->getNext();
            currentField = currentField->getNext();
        }
        information += "\n";

        TreeNode<LinkedList<std::string>>* right = treeNodeFind->getRight();
        TreeNode<LinkedList<std::string>>* left = treeNodeFind->getLeft();
        if(right != nullptr){
            information += findInformation(key, fieldsList,right);
        }
        if(left != nullptr){
            information += findInformation(key, fieldsList, left);
        }

    }catch (const std::invalid_argument& e){
        //ignorar porque no se encontro la informacion
    }
    return information;
}

