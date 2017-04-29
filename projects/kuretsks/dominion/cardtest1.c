#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"
/*	This unit test is designed to test the Adventurer card
 *	implementation. 
 *
 *	Card Effect: Reveal cards from your deck until you reveal
 *	2 Treasure cards. Put those Treasure cards into your hand and
 *	discard the other revealed cards.
 *
 *	Desired Pre-condition: 
 *		-- 	struct gameState game which holds game information. 
 *		  	See dominion.h for full description of struct. 
 *	Desired Post-condition:
 *		--	Current player receives two treasure cards into 
 *			current hand. 
 *		--	Current player discards all other non-Treasure cards.
 *
 * 	**Note: since this is a fresh game init, starting cards should only
 * 	be copper and estate, though this is an assumption. 
 */

int main(int argc, char **argv){
	printf("************************ Testing Adventurer Card... ************************\n\n");

	//Variables
	struct gameState game;
	memset(&game, 'z', sizeof(struct gameState));
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, 
		cutpurse, sea_hag, tribute, smithy};
	int randNum, result, discardBefore, discardAfter, handCountBefore, handCountAfter, error = 0;	
	randNum = rand()%123;

	//Initialzing game with preset values
	result = initializeGame(2, k, randNum, &game);
	
	//Game initialization on successful completion should return zero
	//This is custom assertion (vs. using assertion.h)
	if(result != 0){
		printf("Fail:\tinitializing game returned non-zero value.\n\n");
		exit(1); //Exiting with error since game initialization is required for further tests
	}
	//Setting a random card in player 1's hand as Adventurer
	randNum = rand()%5;
	game.hand[0][randNum] = k[0];

	//Getting discard and hand count before playing Adventurer
	discardBefore = game.discardCount[0];
	handCountBefore = game.handCount[0];	

	//Playing Adventurer card
	result = playAdventurer(&game);

	//Custom assertion: playAdventurer should return zero 
	if(result != 0){
		printf("Fail:\tplaying Adventurer card returned non-zero value.\n\n");
		error = 1;
	}

	//Player's hand should have yielded 2 additional cards and discarded Adventurer,
	//so net total of 6 cards in hand.
	if(game.handCount[0] != 6){
		printf("Fail:\tAdventurer card did not put at least 1 card into player's hand.\n");
		printf("\t* Hand count should be 6 (+2 treasure cards and discard Adventurer.)\n\n");
		error = 1;
	}
	else if(game.handCount[0] <= 5){
		printf("Fail:\tAdventurer card did not put any cards into player's hand.\n\n");
		error = 1;
	}

	//Additional cards should have been treasure cards
	int cardDrawn1 = game.hand[0][game.handCount[0]-1];
	int cardDrawn2 = game.hand[0][game.handCount[0]-2];
	if(cardDrawn1 != copper || cardDrawn2 != copper){
		printf("Fail:\tThe last drawn cards should be copper.\n\n");
		error = 1;
	}

	//Discard after should at least be one (Adventurer card)
	discardAfter = game.discardCount[0];
	if(discardAfter < 1){
		printf("Fail:\tNo cards were discarded after playing Adventurer.\n\n");
		error = 1;
	}
	if(error == 0)
		printf("Adventurer tests passed.\n\n");	
	printf("************************ End of Adventurer Tests ************************\n\n\n");
	return 0;
}

