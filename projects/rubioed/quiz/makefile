CFLAGS = -Wall -fpic -coverage -lm

all: testme
	./testme

testme: testme.c
	gcc $(CFLAGS) -o testme testme.c

clean:
	rm -rf testme
