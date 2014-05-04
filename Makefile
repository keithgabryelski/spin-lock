all: spin-lock-test

spin-lock-test.o: spin-lock-test.c spin-lock.h
spin-lock.o: spin-lock.c spin-lock.h
spin-lock-test: spin-lock.o spin-lock-test.o
	cc -o spin-lock-test spin-lock.o spin-lock-test.o

clean:
	-rm -f *.o spin-lock-test
