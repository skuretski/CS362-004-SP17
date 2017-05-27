#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

#define TESTCARD "village"

#define ASSERT(condition) ((!(condition)) ? (printf("Test failed.\n"), failed++) : printf("Test passed.\n"))

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int failed = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int p1 = 0; int p2 = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

#if (NOISY_TEST == 1)
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
#endif

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
#if (NOISY_TEST == 1)
	printf("\nTest that player gains +1 cards that comes from own pile:\n");
	printf("p1 hand count = %d, expected = %d\n", testG.handCount[p1], G.handCount[p1] + newCards - discarded);
	printf("p1 deck count = %d, expected = %d\n", testG.deckCount[p1], G.deckCount[p1] - newCards + shuffledCards);
	printf("Test that player gains +2 actions:\n");
	printf("p1 action count = %d, expected = %d\n", testG.numActions, G.numActions + 2);
#endif
	ASSERT(testG.handCount[p1] == G.handCount[p1] + newCards - discarded);
	ASSERT(testG.deckCount[p1] == G.deckCount[p1] - newCards + shuffledCards);
	ASSERT(testG.numActions == G.numActions + 2);

#if (NOISY_TEST == 1)
	printf("\nTest for no state change in other player's deck and hand:\n");
	printf("p2 hand count = %d, expected = %d\n", testG.handCount[p2], G.handCount[p2]);
	printf("p2 deck count = %d, expected = %d\n", testG.deckCount[p2], G.deckCount[p2]);
#endif
	ASSERT(testG.handCount[p2] == G.handCount[p2]);
	ASSERT(testG.deckCount[p2] == G.deckCount[p2]);

#if (NOISY_TEST == 1)
	printf("\nNo state change should occur to the victory card piles and kingdom card piles:\n");
	printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	printf("duchy supply count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	printf("province supply count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
	printf("curse supply count = %d, expected = %d\n", testG.supplyCount[curse], G.supplyCount[curse]);
	printf("adventurer supply count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
	printf("embargo supply count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
	printf("village supply count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
	printf("minion supply count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
	printf("mine supply count = %d, expected = %d\n", testG.supplyCount[mine], G.supplyCount[mine]);
	printf("cutpurse supply count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
	printf("sea_hag supply count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
	printf("tribute supply count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
	printf("smithy supply count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
	printf("council_room supply count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);
#endif
	ASSERT(testG.supplyCount[estate] == G.supplyCount[estate]);
	ASSERT(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	ASSERT(testG.supplyCount[province] == G.supplyCount[province]);
	ASSERT(testG.supplyCount[curse] == G.supplyCount[curse]);
	ASSERT(testG.supplyCount[adventurer] == G.supplyCount[adventurer]);
	ASSERT(testG.supplyCount[embargo] == G.supplyCount[embargo]);
	ASSERT(testG.supplyCount[village] == G.supplyCount[village]);
	ASSERT(testG.supplyCount[minion] == G.supplyCount[minion]);
	ASSERT(testG.supplyCount[mine] == G.supplyCount[mine]);
	ASSERT(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]);
	ASSERT(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]);
	ASSERT(testG.supplyCount[tribute] == G.supplyCount[tribute]);
	ASSERT(testG.supplyCount[smithy] == G.supplyCount[smithy]);
	ASSERT(testG.supplyCount[council_room] == G.supplyCount[council_room]);

	if (failed == 0) {
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	} else {
		printf("\n >>>>> FAIL: Testing complete %s <<<<<\n\n", TESTCARD);
	}

	return 0;
}


