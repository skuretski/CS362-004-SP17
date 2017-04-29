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
	struct gameState game;
	memset(&game, 'z', sizeof(struct gameState));  //clearing out struct
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy};
	int randNum, result, discardBefore, discardAfter, handCountBefore, handCountAfter, 
		error = 0;
	randNum = rand()%123;

	result = initializeGame(2, k, randNum, &game);
	if(result != 0){
		printf("Fail:\tInitializing game returned non-zero value.\n\n");
		exit(1);
	}
	//Setting random card in hand to smithy
	randNum = rand()%5;
	game.hand[0][randNum] = k[9];

	//Getting discard number before
	discardBefore = game.discardCount[0];
	
	//Getting hand count before playing Smithy
	handCountBefore = game.handCount[0];
	
	//Playing Smithy
	result = playSmithy(&game, randNum);
	if(result != 0){
		printf("Fail:\tPlaying Smithy should return value of zero.\n\n");
		error = 1;
	}		
	discardAfter = game.discardCount[0];
	handCountAfter = game.handCount[0];
	//There should be one discard card
	if(discardAfter != (discardBefore + 1)){ 
		printf("Fail:\tThere should one discard card after playing Smithy (the Smithy card itself.)\n\n");
		error = 1; 
	//There is one discard card and checking if it is Smithy
	}else{ 
		if(game.discard[0][discardBefore + 1] != k[9]){
			printf("Fail:\tThe discard card should be Smithy.\n\n");
			error = 1;
		}
	}
	
	//The hand should gain a net of 2 cards (+3 cards, - 1 Smithy)
	if(handCountAfter != (handCountBefore + 2)){
		printf("Fail:\tHand count should net 2 cards (+3 cards, -1 Smithy).\n\n");
		error = 1;
	}

	if(!error){
		printf("Success:\t Smithy passes tests.\n\n");
	}

	printf(" *********************** End of Smithy Test ***********************\n\n");  
	return 0;
}
