CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

card1: 
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c cardtest1.c -o cardtest1 -lm -g

card2:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c cardtest2.c -o cardtest2 -lm -g

card3:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c cardtest3.c -o cardtest3 -lm -g

card4:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c cardtest4.c -o cardtest4 -lm -g

unit1:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c unittest1.c -o unittest1 -lm -g

unit2:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c unittest2.c -o unittest2 -lm -g

unit3:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c unittest3.c -o unittest3 -lm -g

unit4:
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.c rngs.c unittest4.c -o unittest4 -lm -g

mytests: card1 card2 card3 card4 unit1 unit2 unit3 unit4

unittestresults: 
	echo "----------------------------- UNIT TESTS --------------------------" &> unittestresults.out
	gcc -o unittest1 dominion.c rngs.c unittest1.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o unittest2 dominion.c rngs.c unittest2.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o unittest3 dominion.c rngs.c unittest3.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o unittest4 dominion.c rngs.c unittest4.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END UNIT TESTS --------------------------------" >> unittestresults.out
	echo "----------------------------- CARD TESTS ------------------------------------" >> unittestresults.out
	gcc -o cardtest1 dominion.c rngs.c cardtest1.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o cardtest2 dominion.c rngs.c cardtest2.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o cardtest3 dominion.c rngs.c cardtest3.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	gcc -o cardtest4 dominion.c rngs.c cardtest4.c -fprofile-arcs -ftest-coverage -std=c99 -lm -g
	cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END OF CARD TESTS -----------------------------" >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
