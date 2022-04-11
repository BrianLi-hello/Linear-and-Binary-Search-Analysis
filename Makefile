vector_search: vector_search.o
	g++ -Wall -Werror -std=c++11 -o vector_search vector_search.o

vector_search.o: vector_search.cc
	g++ -Wall -Werror -std=c++11 -c -o vector_search.o vector_search.cc

clean: 
	rm -f *.o *.dat vector_search