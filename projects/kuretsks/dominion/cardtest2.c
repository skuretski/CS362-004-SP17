#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"

/*	This unit test is designed to test the Smithy card effect.
 *
 *	Card Effect: +3 Cards
 *
 *	Desired Pre-condition: 
 *		-- struct gameState game which holds basic game information
 *		See dominion.h for full description of struct.
 *
 *		-- Smithy card is in player's hand to play
 *
 *	Desired Post-condition:
 *		-- Player gains additional 3 new cards in hand
 *		-- Player discards Smithy card
 *		-- Net number of cards: 2 
 */

int main(int argc, char **argv){
	printf(" *********************** Testing Smithy Card  ***********************\n\n");

	//Variables
	struct gameState gameBefore, gameAfter;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};
	int randNum, result, error = 0;
	randNum = rand()%123;

	result = initializeGame(2, k, randNum, &gameBefore);
	if(result != 0){
		printf("Fail:\tInitializing game returned non-zero value.\n\n");
		exit(1);
	}
	result = initializeGame(2, k, randNum, &gameAfter);
	//Setting random card in hand to smithy
	randNum = rand()%5;
	gameBefore.hand[0][randNum] = k[9];
	gameAfter.hand[0][randNum] = k[9];
	
	//Playing Smithy
	result = playSmithy(&gameAfter, randNum);
	if(result != 0){
		printf("Fail:\tPlaying Smithy should return value of zero.\n\n");
		error = 1;
	}		
	//There should be one playedCard
	if(gameAfter.playedCardCount != 1){ 
		printf("Fail:\tThere should one played card.\n\n");
		error = 1; 
	//The is played card should be a Smithy
	}else if(gameAfter.playedCards[0] != smithy){
		printf("Fail:\tPlayed card should be a Smithy.\n\n");
		error = 1;
	}
	//The hand should gain a net of 2 cards (+3 cards, - 1 Smithy)
	if(gameAfter.handCount[0] != (gameBefore.handCount[0] + 2)){
		printf("Fail:\tHand count should net 2 cards (+3 cards, -1 Smithy).\n\n");
		error = 1;
	}
	//The number of actions should be decremented
	if(gameAfter.numActions != (gameBefore.numActions - 1)){
		printf("Fail:\tNumber of actions should have decreased by 1.\n\n");
		error = 1;
	}
	if(!error){
		printf("Success:\t Smithy passes tests.\n\n");
	}

	printf(" *********************** End of Smithy Test ***********************\n\n");  
	return 0;
}
