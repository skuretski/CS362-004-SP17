/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

#define ASSERT(condition) ((!(condition)) ? (printf("Test failed.\n"), failed++) : printf("Test passed.\n"))

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int failed = 0;
    int p1 = 0; int p2 = 1;
    int r, gain;
    int card = adventurer;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;

    printf ("TESTING gainCard():\n\n");

#if (NOISY_TEST == 1)
    printf("Test that card cannot be gained from empty supply pile:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    G.supplyCount[card] = 0;                         // set supply count to empty
    gain = gainCard(card, &testG, 0, p1);
#if (NOISY_TEST == 1)
    printf("gain = %d, expected = %d\n", gain, -1);
#endif
    ASSERT(gain == -1);                       // check if card wasn't gained

#if (NOISY_TEST == 1)
    printf("Test that card cannot be gained when card is not used in game:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    gain = gainCard(steward, &testG, 0, p1);         // steward is not used in game
#if (NOISY_TEST == 1)
    printf("gain = %d, expected = %d\n", gain, -1);
#endif
    ASSERT(gain == -1);                       // check if card wasn't gained

#if (NOISY_TEST == 1)
    printf("Test flag 0 - card is discarded:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    gain = gainCard(card, &testG, 0, p1);            // card is discarded
#if (NOISY_TEST == 1)
    printf("test game player 1 discardCount = %d, expected = %d\n", testG.discardCount[p1], G.discardCount[p1]+1);
#endif
    ASSERT(testG.discardCount[p1] == G.discardCount[p1]+1); // check that card was discarded from current player's deck
#if (NOISY_TEST == 1)
    printf("test game player 2 discardCount = %d, expected = %d\n", testG.discardCount[p2], G.discardCount[p2]);
#endif
    ASSERT(testG.discardCount[p2] == G.discardCount[p2]); // check that no changes occurred to other player's deck

#if (NOISY_TEST == 1)
    printf("Test flag 1 - card is added to deck:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    gain = gainCard(card, &testG, 1, p1);            // card is added to deck
#if (NOISY_TEST == 1)
    printf("test game player 1 deckCount = %d, expected = %d\n", testG.deckCount[p1], G.deckCount[p1]+1);
#endif
    ASSERT(testG.deckCount[p1] == G.deckCount[p1]+1); // check that card was added to current player's deck
#if (NOISY_TEST == 1)
    printf("test game player 2 deckCount = %d, expected = %d\n", testG.deckCount[p2], G.deckCount[p2]);
#endif
    ASSERT(testG.deckCount[p2] == G.deckCount[p2]); // check that no changes occurred to other player's deck

#if (NOISY_TEST == 1)
    printf("Test flag 2 - card is added to hand:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    gain = gainCard(card, &testG, 2, p1);            // card is added to hand
#if (NOISY_TEST == 1)
    printf("test game player 1 handCount = %d, expected = %d\n", testG.handCount[p1], G.handCount[p1]+1);
#endif
    ASSERT(testG.handCount[p1] == G.handCount[p1]+1); // check that card was added to current player's hand
#if (NOISY_TEST == 1)
    printf("test game player 2 handCount = %d, expected = %d\n", testG.handCount[p2], G.handCount[p2]);
#endif
    ASSERT(testG.handCount[p2] == G.handCount[p2]); // check that no changes occurred to other player's hand

#if (NOISY_TEST == 1)
    printf("Test that supply count is decreased:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    gain = gainCard(card, &testG, 0, p1);
#if (NOISY_TEST == 1)
    printf("test game supplyCount = %d, expected = %d\n", testG.supplyCount[card], G.supplyCount[card]-1);
#endif
    ASSERT(testG.supplyCount[card] == G.supplyCount[card]-1); // check that supplyCount was decreased

    if (failed == 0) {
        printf("\nAll tests passed!\n\n");
    } else {
        printf("\nNot all tests passed.\n\n");
    }

    return 0;
}
