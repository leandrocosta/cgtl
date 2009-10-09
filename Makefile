graph: graph.cpp
	g++ -g -Wall graph.cpp -o graph

clean:
	rm -f graph *~ *.bz2

run:
	./graph

bz2:
	rm -f garph.tar.bz2
	tar -cjvf graph.tar.bz2 *.h *.cpp Makefile
