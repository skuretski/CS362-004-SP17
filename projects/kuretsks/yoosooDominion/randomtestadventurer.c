#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

#define NUM_TESTS 10

#define TESTCARD "adventurer"

//#define ASSERT(condition) ((!(condition)) ? (printf("Test failed.\n"), failed++) : (printf("Test passed.\n"), passed++))
#define ASSERT(condition) ((!(condition)) ? (failed++) : (passed++))

int main() {
	int i;
	int goodtest, badtest = 0;
    int newCards;
    int discarded;
    int isTreasure = 0;
    int treasuresHandBefore, treasuresToAdd, toDiscard, treasuresHandAfter;
    int randCard, shuffledCards = 0;
    int passed = 0; int failed = 0;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int players = 2;
    int p = 0; int p2 = 1;

#if (NOISY_TEST == 1)
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
#endif

	for (i = 0; i < NUM_TESTS; i++) {

		printf("\n\nTest %d:\n\n", i+1);
		//players = (rand() % (MAX_PLAYERS-1)) + 2;  // 2 to 4 players

		// initialize kingdom cards
		int k[10] = {adventurer, embargo, village, minion, great_hall, cutpurse,
				sea_hag, tribute, smithy, council_room};

		struct gameState G, testG;

		treasuresHandBefore = 0;
		treasuresToAdd = 0;
		toDiscard = 0;
		treasuresHandAfter = 0;

		// initialize game state
		initializeGame(players, k, seed, &G);

		// establish random handCount, deckCount, discardCount
		G.handCount[p] = (rand() % 9) + 2; // 2 to 10 cards in hand
		G.deckCount[p] = (rand() % 9) + 2; // 2 to 10 cards in deck

		// establish each card in hand
		// first card in hand is village
		G.hand[p][0] = village;
		int j;
		for (j = 1; j < G.handCount[p]; j++) {
			isTreasure = rand() % 2;
			if (isTreasure == 0) {
				G.hand[p][j] = (rand() % 3) + copper; // add treasure card to hand by random chance
			} else {
				randCard = rand() % 14; // if not a treasure card, choose random card out of 14 other playable cards (1 curse, 3 victory, 10 kingdom)
				if (randCard < copper) {
					G.hand[p][j] = randCard; // if card number is less than copper's, it's a curse/victory card
				} else {
					G.hand[p][j] = k[randCard - copper]; // otherwise it's one of the 10 kingdom cards
				}
			}
		}

#if (NOISY_TEST == 1)
		printf("Hand cards before: ");
		for (j = 0; j < G.handCount[p]; j++) {
			printf("%d ", G.hand[p][j]);
		}
		printf("\n");

		for (j = 0; j < G.handCount[p]; j++) {
			if ((G.hand[p][j] == copper) || (G.hand[p][j] == silver) || (G.hand[p][j] == gold)) {
				treasuresHandBefore++;
			} else {
				continue;
			}
		}
		printf("treasuresHandBefore: %d\n", treasuresHandBefore);
#endif

		// establish each card in deck
		for (j = 0; j < G.deckCount[p]; j++) {
			isTreasure = rand() % 2;
			if (isTreasure == 0) {
				G.deck[p][j] = (rand() % 3) + copper; // add treasure card to hand by random chance
			} else {
				randCard = rand() % 14; // if not a treasure card, choose random card out of 14 other playable cards (1 curse, 3 victory, 10 kingdom)
				if (randCard < copper) {
					G.deck[p][j] = randCard; // if card number is less than copper's, it's a curse/victory card
				} else {
					G.deck[p][j] = k[randCard - copper]; // otherwise it's one of the 10 kingdom cards
				}
			}
		}

#if (NOISY_TEST == 1)
		printf("Deck cards before: ");
		for (j = 0; j < G.deckCount[p]; j++) {
			printf("%d ", G.deck[p][j]);
		}
		printf("\n");

		j = 0;
		while (treasuresToAdd < 2) {
			if ((G.deck[p][j] == copper) || (G.deck[p][j] == silver) || (G.deck[p][j] == gold)) {
				treasuresToAdd++;
			} else {
				toDiscard++;
			}
			j++;
		}
		printf("treasuresToAdd: %d\n", treasuresToAdd);
		printf("toDiscard: %d\n", toDiscard);
#endif

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

#if (NOISY_TEST == 1)
		printf("Playing card...\n");
#endif

		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		newCards = treasuresToAdd + toDiscard;
		discarded = 1 + toDiscard;

#if (NOISY_TEST == 1)
		printf("Hand cards after: ");
		for (j = 0; j < testG.handCount[p]; j++) {
			printf("%d ", testG.hand[p][j]);
		}
		printf("\n");

		for (j = 0; j < testG.handCount[p]; j++) {
			if (testG.hand[p][j] == copper || testG.hand[p][j] == silver || testG.hand[p][j] == gold) {
				treasuresHandAfter++;
			}
		}
		printf("treasuresHandAfter: %d\n", treasuresHandAfter);

		printf("Deck cards after: ");
		for (j = 0; j < testG.deckCount[p]; j++) {
			printf("%d ", testG.deck[p][j]);
		}
		printf("\n");
#endif

#if (NOISY_TEST == 1)
		printf("\nTest that player gains +2 treasure cards that come from own pile:\n"); // Intentional bug: +3 treasure cards instead of 2
		printf("p1 hand count = %d, expected = %d\n", testG.handCount[p], G.handCount[p] + newCards - discarded);
		printf("p1 deck count = %d, expected = %d\n", testG.deckCount[p], G.deckCount[p] - newCards + shuffledCards);
		printf("treasure cards drawn = %d, expected = %d\n", treasuresHandAfter, treasuresToAdd);
#endif
		ASSERT(testG.handCount[p] == G.handCount[p] + newCards - discarded);
		ASSERT(testG.deckCount[p] == G.deckCount[p] - newCards + shuffledCards);
		ASSERT(treasuresHandAfter == treasuresToAdd);

#if (NOISY_TEST == 1)
		printf("\nTest for no state change in other player's deck and hand:\n");
		printf("p2 hand count = %d, expected = %d\n", testG.handCount[p2], G.handCount[p2]);
		printf("p2 deck count = %d, expected = %d\n", testG.deckCount[p2], G.deckCount[p2]);
#endif
		ASSERT(testG.handCount[p2] == G.handCount[p2]);
		ASSERT(testG.deckCount[p2] == G.deckCount[p2]);

#if (NOISY_TEST == 1)
		printf("\nTest for no state change in the victory card piles and kingdom card piles:\n");
		printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
		printf("duchy supply count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
		printf("province supply count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
		printf("curse supply count = %d, expected = %d\n", testG.supplyCount[curse], G.supplyCount[curse]);
		printf("adventurer supply count = %d, expected = %d\n", testG.supplyCount[adventurer], G.supplyCount[adventurer]);
		printf("embargo supply count = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
		printf("village supply count = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village]);
		printf("minion supply count = %d, expected = %d\n", testG.supplyCount[minion], G.supplyCount[minion]);
		printf("mine supply count = %d, expected = %d\n", testG.supplyCount[great_hall], G.supplyCount[great_hall]);
		printf("cutpurse supply count = %d, expected = %d\n", testG.supplyCount[cutpurse], G.supplyCount[cutpurse]);
		printf("sea_hag supply count = %d, expected = %d\n", testG.supplyCount[sea_hag], G.supplyCount[sea_hag]);
		printf("tribute supply count = %d, expected = %d\n", testG.supplyCount[tribute], G.supplyCount[tribute]);
		printf("smithy supply count = %d, expected = %d\n", testG.supplyCount[smithy], G.supplyCount[smithy]);
		printf("council_room supply count = %d, expected = %d\n", testG.supplyCount[council_room], G.supplyCount[council_room]);
#endif
		ASSERT(testG.supplyCount[estate] == G.supplyCount[estate]); // Estate supply count is 2 less than expected due to intentional bug.
		ASSERT(testG.supplyCount[duchy] == G.supplyCount[duchy]);
		ASSERT(testG.supplyCount[province] == G.supplyCount[province]);
		ASSERT(testG.supplyCount[curse] == G.supplyCount[curse]);
		ASSERT(testG.supplyCount[adventurer] == G.supplyCount[adventurer]);
		ASSERT(testG.supplyCount[embargo] == G.supplyCount[embargo]);
		ASSERT(testG.supplyCount[village] == G.supplyCount[village]);
		ASSERT(testG.supplyCount[minion] == G.supplyCount[minion]);
		ASSERT(testG.supplyCount[great_hall] == G.supplyCount[great_hall]);
		ASSERT(testG.supplyCount[cutpurse] == G.supplyCount[cutpurse]);
		ASSERT(testG.supplyCount[sea_hag] == G.supplyCount[sea_hag]);
		ASSERT(testG.supplyCount[tribute] == G.supplyCount[tribute]);
		ASSERT(testG.supplyCount[smithy] == G.supplyCount[smithy]);
		ASSERT(testG.supplyCount[council_room] == G.supplyCount[council_room]);

		if (failed == 0) {
			goodtest++;
		} else {
			badtest++;
		}

	}

	if (failed == 0) {
		printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);
		printf(" >>>>> %d tests passed, %d tests failed, out of %d tests. <<<<<\n", goodtest, badtest, NUM_TESTS);
	} else {
		printf("\n >>>>> FAIL: Testing complete %s <<<<<\n", TESTCARD);
		printf(" >>>>> %d tests passed, %d tests failed, out of %d tests. <<<<<\n", goodtest, badtest, NUM_TESTS);
	}

	printf("\nBugs from previous assignments that are still present in random tests:\n");
	printf("\tDeliberate bug where player draws cards until they have 3 treasure cards instead of 2.\n");
	printf("\tBug where all of player's deck is somehow added to their hand.\n");
	printf("\tOther player's hand count is one card more than expected, and deck count one card less than expected.\n\n");

	return 0;
}


