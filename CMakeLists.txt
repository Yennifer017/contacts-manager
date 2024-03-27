cmake_minimum_required(VERSION 3.27)
project(contacts_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(contacts_manager main.cpp
        Token.cpp
        Token.h
        Reguex.cpp
        Reguex.h
        Lexer.cpp
        Lexer.h
        LinkedList.h
        Node.h
        TypeTkn.h
        Util.cpp
        Util.h
        HashContainer.h
        HashMap.h
        TreeNode.h
        AVLtree.h
        Exporter.cpp
        Exporter.h
        Manager.cpp
        Manager.h
        TreeGraficator.h
        Group.cpp
        Group.h
        Field.cpp
        Field.h
        Translator.cpp
        Translator.h
        Reportero.cpp
        Reportero.h
)
