/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-04
 * PROJECT: Assignment 3
 * DESCRIPTION: Provide unit test for Village card
 ******************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include "rngs.h"

 #define assertExit 0

 void asserttrue(int test, int exitOnFail);

 void testVillageCard(struct gameState *state) {
   // Store a copy of the gameState before the card is played
   struct gameState pre;
   memcpy (&pre, state, sizeof(struct gameState));

   int player = whoseTurn(state);
   int villagePos = state->handCount[player] - 1;

   playCard(villagePos, adventurer, gardens, embargo, state);

   printf("Test Village: ");
   asserttrue(state->playedCards[state->playedCardCount-1] == village, assertExit);
   printf(": test village card is in playedCard pile after being played\n");

   printf("Test Village: ");
   asserttrue(state->handCount[player] == (pre.handCount[player]), assertExit);
   printf(": hand count stayed the same after village was played and another card was drawn\n");

   printf("Test Village: ");
   asserttrue(state->numActions == (pre.numActions + 1), assertExit);
   printf(": numActions was increased by 1 after village was played and 2 actions added\n");
 }

 int main(int argc, char const *argv[]) {
   // create a game
   int seed = 10;
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};
   initializeGame(2, k, seed, &G);

   // draw village into hand
   int gainToHand = 2;
   gainCard(village, &G, gainToHand, whoseTurn(&G));

   testVillageCard(&G);
   return 0;
 }
