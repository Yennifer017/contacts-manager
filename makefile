#variable global de compilador de c++
CPP = g++
#definiendo el programa final
TARGET = contacts_manager

#compilar el programa principal, se declaran las dependencias (todos los archivos)
all: .all-post

.all-post: AVLtree.o DotFileExecutor.o Exporter.o Field.o Grapher.o Group.o HashContainer.o HashMap.o HashTableGrapher.o Lexer.o LinkedList.o Manager.o Node.o Parser.o Reguex.o Reportero.o Searcher.o Token.o Translator.o TreeGraficator.o TreeNode.o TypeTkn.o Util.o main.o

	$(CPP) AVLtree.o DotFileExecutor.o Exporter.o Field.o Grapher.o Group.o HashContainer.o HashMap.o HashTableGrapher.o Lexer.o LinkedList.o Manager.o Node.o Reguex.o Reportero.o Searcher.o Token.o Translator.o TreeGraficator.o TreeNode.o TypeTkn.o Util.o main.o -o $(TARGET)

AVLtree.o: AVLtree.h
	touch AVLtree.o
	
DotFileExecutor.o: DotFileExecutor.cpp DotFileExecutor.h
	$(CPP) -c DotFileExecutor.cpp
	
Exporter.o: Exporter.cpp Exporter.h
	$(CPP) -c Exporter.cpp 
	
Field.o: Field.cpp Field.h
	$(CPP) -c Field.cpp
	
Grapher.o: Grapher.cpp Grapher.h
	$(CPP) -c Grapher.cpp
	
Group.o: Group.cpp Group.h
	$(CPP) -c Group.cpp

HashContainer.o: HashContainer.h 
	touch HashContainer.o
HashMap.o: HashMap.h
	touch HashMap.o
HashTableGrapher.o: HashTableGrapher.h
	touch HashTableGrapher.o

Lexer.o: Lexer.cpp Lexer.h
	$(CPP) -c Lexer.cpp
LinkedList.o: LinkedList.h
	touch LinkedList.o
 
Manager.o: Manager.cpp Manager.h
	$(CPP) -c Manager.cpp
 
Node.o: Node.h
	touch Node.o
	
Parser.o: Parser.cpp Parser.h
	$(CPP) -c Parser.cpp
	
Reguex.o: Reguex.cpp Reguex.h
	$(CPP) -c Reguex.cpp
 
Reportero.o: Reportero.cpp Reportero.h
	$(CPP) -c Reportero.cpp
 
Searcher.o: Searcher.h
	touch Searcher.o

Token.o: Token.cpp Token.h
	$(CPP) -c Token.cpp
	
Translator.o: Translator.cpp Translator.h
	$(CPP) -c Translator.cpp
	
TreeGraficator.o: TreeGraficator.h
	touch TreeGraficator.o
	
TreeNode.o: TreeNode.h
	touch TreeNode.o
	
TypeTkn.o: TypeTkn.h
	touch TypeTkn.o

Util.o: Util.cpp Util.h
	$(CPP) -c Util.cpp
	
main.o: 
	$(CPP) -c main.cpp


# tener un comando para eliminar todos los archivos .o generados
clean:
	rm -f *.o $(TARGET)
