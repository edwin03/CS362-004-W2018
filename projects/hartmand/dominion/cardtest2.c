/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-04
 * PROJECT: Assignment 3
 * DESCRIPTION: Provide unit test for Adventurer card
 ******************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include "rngs.h"

 #define assertExit 0

 void asserttrue(int test, int exitOnFail);

 void testAdventurerCard(struct gameState *state) {
   // Store a copy of the gameState before the card is played
   struct gameState pre;
   memcpy (&pre, state, sizeof(struct gameState));

   int player = whoseTurn(state);
   int adventurerPos = state->handCount[player] - 1;
   int i;
   int card;
   int preTreasures, postTreasures;

   playCard(adventurerPos, smithy, gardens, embargo, state);

   // test that total coppers + silver + gold is same before and after
   printf("Test Adventurer: ");
   asserttrue(
     (fullDeckCount(player, copper, state) +
     fullDeckCount(player, silver, state) +
     fullDeckCount(player, gold, state)) ==
     (fullDeckCount(player, copper, &pre) +
     fullDeckCount(player, silver, &pre) +
     fullDeckCount(player, gold, &pre))
     , assertExit);
   printf(": total coppers, silvers, and gold hasn't changed\n");

   // test that coppers + silver + gold in hand is 2 more than before
   printf("Test Adventurer: ");
   preTreasures = postTreasures = 0;
   for (i=0; i<state->handCount[player]; i++) {
     card = state->hand[player][i];
     if (card == copper || card == silver || card == gold)
       postTreasures++;
   }
   for (i=0; i<pre.handCount[player]; i++) {
     card = pre.hand[player][i];
     if (card == copper || card == silver || card == gold)
       preTreasures++;
   }
   asserttrue(postTreasures == (preTreasures+2), assertExit);
   printf(": test that coppers + silvers + gold in hand is 2 more than before\n");

   // test that coppers + silver + gold in deck and discard is 2 less than before
   printf("Test Adventurer: ");
   preTreasures = postTreasures = 0;
   // get treasures in deck from after the card was played
   for (i=0; i<state->deckCount[player]; i++) {
     card = state->deck[player][i];
     if (card == copper || card == silver || card == gold)
       postTreasures++;
   }
   // get treasures in discard from after the card was played
   for (i=0; i<state->discardCount[player]; i++) {
     card = state->discard[player][i];
     if (card == copper || card == silver || card == gold)
       postTreasures++;
   }
   // get treasures in deck from after the card was played
   for (i=0; i<pre.deckCount[player]; i++) {
     card = pre.deck[player][i];
     if (card == copper || card == silver || card == gold)
       preTreasures++;
   }
   // get treasures in discard from after the card was played
   for (i=0; i<pre.discardCount[player]; i++) {
     card = pre.discard[player][i];
     if (card == copper || card == silver || card == gold)
       preTreasures++;
   }
   asserttrue(postTreasures == (preTreasures-2), assertExit);
   printf(": test that coppers + silvers + gold in deck and hand is 2 less than before\n");
 }

 int main(int argc, char const *argv[]) {
   // create a game
   int seed = 1000;
   struct gameState G;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy};
   initializeGame(2, k, seed, &G);

   // draw adventurer into hand
   int gainToHand = 2;
   gainCard(adventurer, &G, gainToHand, whoseTurn(&G));

   testAdventurerCard(&G);
   return 0;
 }
