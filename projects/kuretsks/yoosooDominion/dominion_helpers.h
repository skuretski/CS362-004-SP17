#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
	       struct gameState *state, int handPos, int *bonus);

int useSmithy(struct gameState *state, int i, int currentPlayer, int handPos);
int useAdventurer(struct gameState *state, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[MAX_HAND], int tmpCounter);
int useVillage(struct gameState *state, int currentPlayer, int handPos);
int useGreat_Hall(struct gameState *state, int currentPlayer, int handPos);
int useSteward(struct gameState *state, int choice1, int choice2, int choice3, int currentPlayer, int handPos);
int useSalvager(struct gameState *state, int choice1, int currentPlayer, int handPos);

#endif