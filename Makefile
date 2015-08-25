all: BinarySearchTree.h DSexceptions.h MyExceptions.h Driver.o Indexer.o Word.o
	g++ -ansi -Wall BinarySearchTree.h MyExceptions.h Driver.o Indexer.o Word.o -o Driver.out

Word.o: Word.cpp
	g++ -ansi -Wall -c Word.cpp

Indexer.o: Indexer.cpp
	g++ -ansi -Wall -c Indexer.cpp

Driver.o: Driver.cpp
	g++ -ansi -Wall -c Driver.cpp

run:
	./Driver.out $(STRING) $(STRING)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~*.h.gch *#[
