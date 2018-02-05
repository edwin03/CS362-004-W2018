/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-04
 * PROJECT: Assignment 3
 * DESCRIPTION: Provide unit test for Council card
 ******************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include "rngs.h"

 #define assertExit 0

 void asserttrue(int test, int exitOnFail);

 void testCouncilRoomCard(struct gameState *state) {
   // Store a copy of the gameState before the card is played
   struct gameState pre;
   memcpy (&pre, state, sizeof(struct gameState));

   int player = whoseTurn(state);
   int councilRoomPos = state->handCount[player] - 1;
   int i;

   playCard(councilRoomPos, adventurer, gardens, embargo, state);

   printf("PreHandCount:  %d\n", pre.handCount[player]);
   printf("PostHandCount: %d\n", state->handCount[player]);

   printf("Test Council Room: ");
   asserttrue(state->playedCards[state->playedCardCount-1] == council_room, assertExit);
   printf(": test councilRoom card is in playedCard pile after being played\n");

   printf("Test Council Room: ");
   asserttrue(state->handCount[player] == (pre.handCount[player]+3), assertExit);
   printf(": hand count increased by 3 after councilRoom was played and 4 cards were drawn\n");

   // All other players gained a card
   for (i=0; i<state->numPlayers; i++) {
     if (i != player) {
       printf("Test Council Room: ");
       asserttrue(state->handCount[i] == (pre.handCount[i]+1), assertExit);
       printf(": opponent player %d gained a card\n", i);
     }
   }

   printf("Test Council Room: ");
   asserttrue(state->numBuys == (pre.numBuys + 1), assertExit);
   printf(": numBuys was increased by 1\n");
 }

 int main(int argc, char const *argv[]) {
   // create a game
   int seed = 10;
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
            council_room, tribute, smithy};
   initializeGame(2, k, seed, &G);

   // draw council_room into hand
   int gainToHand = 2;
   gainCard(council_room, &G, gainToHand, whoseTurn(&G));

   testCouncilRoomCard(&G);
   return 0;
 }
