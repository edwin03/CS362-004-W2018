CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

randomtestcard1.out: randomtestcard1.c asserttrue.c dominion.o rngs.o
	gcc -o randomtestcard1 $< asserttrue.c dominion.o rngs.o $(CFLAGS)
	echo "Results for running randomtestcard1:" > $@
	./randomtestcard1 >> $@
	gcov dominion.c >> $@

randomtestcard2.out: randomtestcard2.c asserttrue.c dominion.o rngs.o
	gcc -o randomtestcard2 $< asserttrue.c dominion.o rngs.o $(CFLAGS)
	echo "Results for running randomtestcard2:" > $@
	./randomtestcard2 >> $@
	gcov dominion.c >> $@

randomtestadventurer.out: randomtestadventurer.c asserttrue.c dominion.o rngs.o
	gcc -o randomtestadventurer $< asserttrue.c dominion.o rngs.o $(CFLAGS)
	echo "Results for running randomtestadventurer:" > $@
	./randomtestadventurer >> $@
	gcov dominion.c >> $@

unittestresult.out: asserttrue.c unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Result for running unit tests:" > unittestresult.out

	echo "unittest1.c:" >> unittestresult.out
	gcc -o unittest1 -g asserttrue.c unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "unittest2.c:" >> unittestresult.out
	gcc -o unittest2 -g asserttrue.c unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "unittest3.c:" >> unittestresult.out
	gcc -o unittest3 -g asserttrue.c unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "unittest4.c:" >> unittestresult.out
	gcc -o unittest4 -g asserttrue.c unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest1.c:" >> unittestresult.out
	gcc -o cardtest1 -g asserttrue.c cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest2.c:" >> unittestresult.out
	gcc -o cardtest2 -g asserttrue.c cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest3.c:" >> unittestresult.out
	gcc -o cardtest3 -g asserttrue.c cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

	echo "cardtest4.c:" >> unittestresult.out
	gcc -o cardtest4 -g asserttrue.c cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer
