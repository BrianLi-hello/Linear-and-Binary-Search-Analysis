vector_search: vector_search.cc
	g++ -Wall -Werror -std=c++11 -o vector_search vector_search.cc

clean: 
	rm -f *.dat vector_search
