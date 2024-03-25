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
        HashTable.h
        HashContainer.h
        HashMap.h
)
