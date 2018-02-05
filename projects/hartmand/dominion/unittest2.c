/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-04
 * PROJECT: Assignment 3
 * DESCRIPTION:
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define assertExit 0

void asserttrue(int test, int exitOnFail);

void testBuyCard(struct gameState *state) {
  // Store a copy of the gameState before the card is played
  struct gameState pre;
  memcpy (&pre, state, sizeof(struct gameState));

  int player = whoseTurn(state);
  int r;

  // buy adventurer - cost 6 - too expensive
  r = buyCard(adventurer, state);
  printf("buyCard(): ");
  asserttrue(pre.discardCount[player] == state->discardCount[player] && memcmp(pre.discard[player], state->discard[player], sizeof(int)*MAX_DECK) == 0, assertExit);
  printf(": attempt to buy a card that costs too much - deck doesn't change\n");

  printf("buyCard(): ");
  asserttrue(state->coins == pre.coins, assertExit);
  printf(": attempt to buy a card that costs too much - coin doesn't change\n");

  // buy smithy - cost 4
  r = buyCard(smithy, state);
  printf("buyCard(): ");
  asserttrue(state->discardCount[player] == pre.discardCount[player]+1, assertExit);
  printf(": buy a card - discard increases by 1\n");

  printf("buyCard(): ");
  asserttrue(state->coins == (pre.coins - getCost(smithy)), assertExit);
  printf(": buy a card - coins go down\n");

  printf("buyCard(): ");
  asserttrue(state->numBuys == (pre.numBuys - 1), assertExit);
  printf(": buy a card - number of buys goes down by 1\n");
}

int main(int argc, char const *argv[]) {
  // create a game
  int seed = 1000;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, seed, &G);

  testBuyCard(&G);
  return 0;
}
