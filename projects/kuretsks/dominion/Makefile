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

card1: cardtest1.c dominion.o rngs.o interface.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 interface.o dominion.o rngs.o cardtest1.c -o cardtest1 -lm -g

card2: cardtest2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest2.c -o cardtest2 -lm -g

card3: cardtest3.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest3.c -o cardtest3 -lm -g

card4: cardtest4.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o cardtest4.c -o cardtest4 -lm -g

unit1: unittest1.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o unittest1.c -o unittest1 -lm -g

unit2: unittest2.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o unittest2.c -o unittest2 -lm -g

unit3: unittest3.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o unittest3.c -o unittest3 -lm -g

unit4: unittest4.c rngs.o dominion.o
	gcc -fprofile-arcs -ftest-coverage -std=c99 dominion.o rngs.o unittest4.c -o unittest4 -lm -g

mytests: card1 card2 card3 card4 unit1 unit2 unit3 unit4

unittestresults.out: 
	echo "----------------------------- UNIT TESTS --------------------------" &> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END UNIT TESTS --------------------------------" >> unittestresults.out
	echo "----------------------------- CARD TESTS ------------------------------------" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out
	echo "----------------------------- END OF CARD TESTS -----------------------------" >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
mytesthelper.o: mytesthelper.h mytesthelper.c rngs.o dominion.o
	gcc -c mytesthelper.c $(CFLAGS)

randadvcard: randomtestadventurer.c dominion.o rngs.o mytesthelper.o interface.o
	gcc -o randadvcard -g randomtestadventurer.c dominion.o rngs.o mytesthelper.o interface.o -std=c99 -fprofile-arcs -ftest-coverage -lm

randtestcard2: randomtestcard2.c dominion.o rngs.o mytesthelper.o
	gcc -o randtestcard2 -g randomtestcard2.c dominion.o rngs.o mytesthelper.o -std=c99 -fprofile-arcs -ftest-coverage -lm
		
randtestcard1: randomtestcard1.c dominion.o rngs.o mytesthelper.o
	gcc -o randtestcard1 -g randomtestcard1.c dominion.o rngs.o mytesthelper.o -std=c99 -fprofile-arcs -ftest-coverage -lm
	
randomtestcard1.out:
	echo "----------------------------------- RANDOM TEST CARD 1 ------------------------------------------------" &> randomtestcard1.out
	./randtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	echo "----------------------------------- END OF RANDOM TEST CARD 1 -----------------------------------------" >> randomtestcard1.out

randomtestcard2.out:
	echo "----------------------------------- RANDOM TEST CARD 2 ------------------------------------------------" &> randomtestcard2.out
	./randtestcard2 >> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	echo "----------------------------------- END OF RANDOM TEST CARD 2 -----------------------------------------" >> randomtestcard2.out
	
randomtestadventurer.out:
	echo "----------------------------------- RANDOM TEST ADVENTURER ------------------------------------------------" &> randomtestadventurer.out
	./randadvcard >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out
	echo "----------------------------------- END OF RANDOM ADVENTURER -----------------------------------------" >> randomtestadventurer.out

myrandomtests: randadvcard randtestcard1 randtestcard2
		
all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o *.exe playdom test player player.exe randtestcard1 randtestcard2 randadvcard mytesthelper testInit *.gcov *.gcda *.gcno *.so unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
