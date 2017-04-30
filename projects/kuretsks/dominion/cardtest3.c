#include <stdlib.h>
#include <stdio.h>
#include "dominion.h"
#include "rngs.h"

/*	This unit test is designed to test the Village card. 
 *
 *	Card Effect: gives player +1 card, +2 actions.
 *
 *	Desired Pre-conditions: 
 *		-- struct gameState game: holds game information 
 *		-- Player has Village card in hand
 *	Desired Post-condition:
 *		-- Player receives +1 card
 *		-- Player receives + 2 action
 */
 
int main(int argc, char **argv){
	printf("********************* Testing Village Card *******************\n\n");
	
	//Variables
	struct gameState gameBefore, gameAfter;
	int result, randNum, error = 0;
	randNum = rand()%123;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy};

	result = initializeGame(2, k, randNum, &gameBefore);	
	if(result){
		printf("Initializing game should return zero.\n\n");
		exit(1);
	}
	gameBefore.hand[0][0] = village;
	gameAfter = gameBefore;

	result = playVillage(&gameAfter, 0);
	if(result){
		printf("Playing Village should return zero.\n\n");
		error = 1;
	}
	// Number of Actions (Num of actions for playing Village itself 
	// is decremented outside of cardEffect. It is in function playCard).
	if(gameAfter.numActions != (gameBefore.numActions + 2)){
		printf("Fail:\tVillage should add 2 actions.\n\n");
		error = 1;
	}

	// Hand Count
	if(gameAfter.handCount[0] != (gameBefore.handCount[0])){
		printf("Fail:\tVillage should have a zero net gain to hand count (+1 card, -1 Village).\n\n");
		error = 1;
	}
	else if(gameAfter.hand[0][0] == village){
		printf("Fail:\tVillage should not be in hand.\n\n");
		error = 1;
	} 
	
	// Played Card
	if(gameAfter.playedCardCount != (gameBefore.playedCardCount + 1)){
		printf("Fail:\tVillage should have increased playedCardCount by 1.\n\n");
		error = 1;
	}
	else if(gameAfter.playedCards[gameAfter.playedCardCount - 1]){
		printf("Fail:\tVillage should be the last card played.\n\n");
		error = 1;
	}
	
	if(!error){
		printf("VILLAGE PASSED ALL TESTS.\n\n");
	}
	printf("*********************** End of Village Testing ****************************\n\n");

	return 0;
}

