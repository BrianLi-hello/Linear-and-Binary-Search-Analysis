# Creating a vector_search object file "unnecessary" since there is only one source file
#vector_search: vector_search.o
#	g++ -Wall -Werror -std=c++11 -o vector_search vector_search.o
#
#vector_search.o: vector_search.cc
#	g++ -Wall -Werror -std=c++11 -c -o vector_search.o vector_search.cc
#
#clean: 
#	rm -f *.o *.dat vector_search

vector_search: vector_search.cc
	g++ -Wall -Werror -std=c++11 -o vector_search vector_search.cc

clean: 
	rm -f *.dat vector_search
