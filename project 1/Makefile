CC = g++ -std=c++14
DEBUG = -g
CFLAGS = -c -Wall -Wextra -pedantic
LFLAGS = -Wall -Wextra -pedantic

all:
	${CC} ${DEBUG} ${LFLAGS} main.cpp -o project1
	make clean

clean:
	rm -f *.o

cleanall: clean
	rm -f project1