#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int *n, *m;
    struct gameState G;

    printf ("TESTING kingdomCards():\n\n");

#if (NOISY_TEST == 1)
    printf("Test that kingdom card values are assigned correctly:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    // make new set of kingdom cards to test
    n = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);

#if (NOISY_TEST == 1)
    printf("Saved cards: %d %d %d %d %d %d %d %d %d %d\n", n[0], n[1], n[2], n[3], n[4], n[5], n[6], n[7], n[8], n[9]);
    printf("Expected cards: %d %d %d %d %d %d %d %d %d %d\n", adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);
#endif
    for (i = 0; i < 10; i++) {
        assert(n[i] == k[i]);
    }

#if (NOISY_TEST == 1)
    printf("Test that kingdom card values are assigned correctly with a new set of cards:\n");
#endif
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    // make new set of kingdom cards
    int j[10] = {embargo, council_room, feast, cutpurse, minion, tribute, sea_hag, village, baron, great_hall};
    r = initializeGame(numPlayer, j, seed, &G); // initialize a new game
    // make new set of kingdom cards to test
    m = kingdomCards(embargo, council_room, feast, cutpurse, minion, tribute, sea_hag, village, baron, great_hall);

#if (NOISY_TEST == 1)
    printf("Saved cards: %d %d %d %d %d %d %d %d %d %d\n", m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8], m[9]);
    printf("Expected cards: %d %d %d %d %d %d %d %d %d %d\n", embargo, council_room, feast, cutpurse, minion, tribute, sea_hag, village, baron, great_hall);
#endif
    for (i = 0; i < 10; i++) {
        assert(m[i] == j[i]);
    }

    printf("\nAll tests passed!\n\n");

    return 0;
}
