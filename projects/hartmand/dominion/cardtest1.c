/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-04
 * PROJECT: Assignment 3
 * DESCRIPTION: Provide unit test for Smithy card
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define assertExit 0

void asserttrue(int test, int exitOnFail);

void testSmithyCard(struct gameState *state) {
  // Store a copy of the gameState before the card is played
  struct gameState pre;
  memcpy (&pre, state, sizeof(struct gameState));

  int player = whoseTurn(state);
  int smithyPos = state->handCount[player] - 1;
  int foundCard;
  int handPos, deckPos, cardsChecked, discardPos, p;    // loop vars

  playCard(smithyPos, adventurer, gardens, embargo, state);

  // Check that 3 cards were drawn. +1 to account for discarded smithy
  int numOfCardsDrawn = state->handCount[player] - pre.handCount[player] + 1;
  asserttrue(numOfCardsDrawn == 3, assertExit);
  printf(": player %d drew three cards\n", player);

  // Check the new cards came from the player's deck
  foundCard = 1;
  for (handPos=smithyPos, deckPos=(pre.deckCount[player]), cardsChecked=0;
      foundCard && handPos < state->handCount[player]; handPos++, deckPos--, cardsChecked++) {
    foundCard = 0;

    // The last card drawn would've been moved forward into the position where
    //   the smithy was when it was discarded so that card is a special case
    //   that must be checked
    if (cardsChecked == 0 && numOfCardsDrawn <= pre.deckCount[player]) {
      if (state->hand[player][handPos] == pre.deck[player][pre.deckCount[player]-numOfCardsDrawn]) {
        // printf("Found special case card: %d\n", state->hand[player][handPos]);
        foundCard = 1;
      }
    }
    // Check the player's deck if there are enough cards in it
    else if (cardsChecked > 0 && deckPos >= 0) {
      if (state->hand[player][handPos] == pre.deck[player][deckPos]) {
        // printf("Found in deck: %d\n", state->hand[player][handPos]);
        foundCard = 1;
      }
    }
    // Otherwise check the player's discard pile
    else {
      for (discardPos = 0; discardPos < pre.discardCount[player]; discardPos++) {
        if (state->hand[player][handPos] == pre.discard[player][discardPos]) {
          foundCard = 1;
          // printf("Found in discard: %d\n", state->hand[player][handPos]);
          break;
        }
      }
    }
  }
  asserttrue(foundCard, assertExit);
  printf(": all drawn cards came from the player %d's deck\n", player);

  // Check the other players' statuses did not change
  for (p=0; p<state->numPlayers; p++) {
    if (p != player) {
      asserttrue(pre.handCount[p] == state->handCount[p] && memcmp(pre.hand[p], state->hand[p], sizeof(int)*MAX_HAND) == 0, assertExit);
      printf(": no changes to player %d's hand\n", p);

      asserttrue(pre.deckCount[p] == state->deckCount[p] && memcmp(pre.deck[p], state->deck[p], sizeof(int)*MAX_DECK) == 0, assertExit);
      printf(": no changes to player %d's deck\n", p);

      asserttrue(pre.discardCount[p] == state->discardCount[p] && memcmp(pre.discard[p], state->discard[p], sizeof(int)*MAX_DECK) == 0, assertExit);
      printf(": no changes to player %d's discard\n", p);
    }
  }

  // Check the game's supply count did not change
  asserttrue(memcmp(pre.supplyCount, state->supplyCount, sizeof(int) * (treasure_map+1)) == 0, assertExit);
  printf(": no changes were made to supplyCount\n");
}

int main(int argc, char const *argv[]) {
  // create a game
  int seed = 10;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, seed, &G);

  // draw smithy into hand
  int gainToHand = 2;
  gainCard(smithy, &G, gainToHand, whoseTurn(&G));

  testSmithyCard(&G);
  return 0;
}
