#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int r, gameOver;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState testG;

    printf ("TESTING isGameOver():\n\n");

#if (NOISY_TEST == 1)
    printf("Test that game is over when province pile is empty:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    testG.supplyCount[province] = 0;                 // set province pile to empty
    gameOver = isGameOver(&testG);
#if (NOISY_TEST == 1)
    printf("gameOver = %d, expected = %d\n", gameOver, 1);
#endif
    assert(gameOver == 1); // check if game ended

#if (NOISY_TEST == 1)
    printf("Test that game is over when three supply piles are empty:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    testG.supplyCount[copper] = 0;                   // set copper pile to empty
    testG.supplyCount[duchy] = 0;                    // set duchy pile to empty
    testG.supplyCount[feast] = 0;                    // set feast pile to empty
    gameOver = isGameOver(&testG);
#if (NOISY_TEST == 1)
    printf("gameOver = %d, expected = %d\n", gameOver, 1);
#endif
    assert(gameOver == 1); // check if game ended

#if (NOISY_TEST == 1)
    printf("Test that game is not over when supply piles are not empty:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    testG.supplyCount[copper] = 0;                   // set copper pile to empty
    testG.supplyCount[duchy] = 1;                    // set duchy pile to not empty
    testG.supplyCount[feast] = 2;                    // set feast pile to not empty
    gameOver = isGameOver(&testG);
#if (NOISY_TEST == 1)
    printf("gameOver = %d, expected = %d\n", gameOver, 0);
#endif
    assert(gameOver == 0); // check if game is not ended

#if (NOISY_TEST == 1)
    printf("Test that game is not over when less than three supply piles are empty:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));        // clear the game state
    r = initializeGame(numPlayer, k, seed, &G);      // initialize a new game
    memcpy(&testG, &G, sizeof(struct gameState));    // create a test copy of the game state
    testG.supplyCount[copper] = 0;                   // set copper pile to empty
    testG.supplyCount[duchy] = 0;                    // set duchy pile to empty
    gameOver = isGameOver(&testG);
#if (NOISY_TEST == 1)
    printf("gameOver = %d, expected = %d\n", gameOver, 0);
#endif
    assert(gameOver == 0); // check if game is not ended


    printf("\nAll tests passed!\n\n");

    return 0;
}
