#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"

/*	This unit test is designed to test the function numHandCards() in
 *	dominion.c.
 *
 *	Function effect: returns the number of hand cards in a player's hand.
 *
 *	Desired Pre-condition: 
 *		-- struct gameState: this holds pertinent game information 
 *			See dominion.h for full detail.
 *
 *	Desired Post-condition:
 *		-- returns correct value of the number of hand card's in a player's
 *			hand
 */ 

int main(int argc, char **argv){
	printf("************************* Testing numHandCards() Function ************************************\n\n");
	
	//Variables
	struct gameState game;
	int k[10] = {1,2,3,4,5,6,7,8,9,0};
	int randNum, result, handCardFunc, handCardStruct, error = 0;

	//Initializing New Game
	randNum = rand()%123;
	result = initializeGame(2, k, randNum, &game);
	if(result != 0){
		printf("Fail:\tGame initialization should return zero.\n\n");
		exit(1);
	}
	
	handCardFunc = numHandCards(&game);
	handCardStruct = game.handCount[0];

	if(handCardFunc != handCardStruct){
		printf("Fail:\tNumber of hand cards from function should equal the number of hand cards from the struct.\n\n");
		error = 1;
	}
	
	//Printing Results
	if(!error){
		printf("numHandCards() PASSED ALL TESTS.\n\n");
	}
	printf("****************************** numHandCards() Tests Completed ************************************\n\n");
	return 0;
}
