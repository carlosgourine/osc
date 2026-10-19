all: sizes.c  sizes.h
	gcc -Wall  sizes.c  -o sizes
sizes: sizes.c  sizes.h
	gcc -Wall sizes.c -o sizes
test: test.c test.h
	gcc -Wall test.c -o test

strings: strings.c strings.h
	gcc -Wall strings.c -o strings

stepwise: sizes.o 
	gcc -o sizes sizes.o

sizes.o: sizes.c sizes.h
	gcc -c sizes.c

clean:
	rm -f *.o
