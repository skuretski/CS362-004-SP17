#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int cost;
    int seed = 1000;

    printf ("TESTING getCost():\n\n");

    // for each card, make sure the return cost value is correct
    cost = getCost(curse);
    assert(cost == 0);
#if (NOISY_TEST == 1)
    printf("curse cost = %d, expected = %d\n", cost, 0);
#endif
    cost = getCost(estate);
    assert(cost == 2);
#if (NOISY_TEST == 1)
    printf("estate cost = %d, expected = %d\n", cost, 2);
#endif
    cost = getCost(duchy);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("duchy cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(province);
    assert(cost == 8);
#if (NOISY_TEST == 1)
    printf("province cost = %d, expected = %d\n", cost, 8);
#endif
    cost = getCost(copper);
    assert(cost == 0);
#if (NOISY_TEST == 1)
    printf("copper cost = %d, expected = %d\n", cost, 0);
#endif
    cost = getCost(silver);
    assert(cost == 3);
#if (NOISY_TEST == 1)
    printf("silver cost = %d, expected = %d\n", cost, 3);
#endif
    cost = getCost(gold);
    assert(cost == 6);
#if (NOISY_TEST == 1)
    printf("gold cost = %d, expected = %d\n", cost, 6);
#endif
    cost = getCost(adventurer);
    assert(cost == 6);
#if (NOISY_TEST == 1)
    printf("adventurer cost = %d, expected = %d\n", cost, 6);
#endif
    cost = getCost(council_room);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("council_room cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(feast);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("feast cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(gardens);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("gardens cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(mine);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("mine cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(remodel);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("remodel cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(smithy);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("smithy cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(village);
    assert(cost == 3);
#if (NOISY_TEST == 1)
    printf("village cost = %d, expected = %d\n", cost, 3);
#endif
    cost = getCost(baron);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("baron cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(great_hall);
    assert(cost == 3);
#if (NOISY_TEST == 1)
    printf("great_hall cost = %d, expected = %d\n", cost, 3);
#endif
    cost = getCost(minion);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("minion cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(steward);
    assert(cost == 3);
#if (NOISY_TEST == 1)
    printf("steward cost = %d, expected = %d\n", cost, 3);
#endif
    cost = getCost(tribute);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("tribute cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(ambassador);
    assert(cost == 3);
#if (NOISY_TEST == 1)
    printf("ambassador cost = %d, expected = %d\n", cost, 3);
#endif
    cost = getCost(cutpurse);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("cutpurse cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(embargo);
    assert(cost == 2);
#if (NOISY_TEST == 1)
    printf("embargo cost = %d, expected = %d\n", cost, 2);
#endif
    cost = getCost(outpost);
    assert(cost == 5);
#if (NOISY_TEST == 1)
    printf("outpost cost = %d, expected = %d\n", cost, 5);
#endif
    cost = getCost(salvager);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("salvager cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(sea_hag);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("sea_hag cost = %d, expected = %d\n", cost, 4);
#endif
    cost = getCost(treasure_map);
    assert(cost == 4);
#if (NOISY_TEST == 1)
    printf("treasure_map cost = %d, expected = %d\n", cost, 4);
#endif

    printf("\nAll tests passed!\n\n");

    return 0;
}
