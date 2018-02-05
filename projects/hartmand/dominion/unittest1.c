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

void testDiscardCard(struct gameState *state) {
  // Store a copy of the gameState before the card is played
  struct gameState pre;
  memcpy (&pre, state, sizeof(struct gameState));

  int player = whoseTurn(state);

  discardCard(0, player, state, 0);
  printf("discardCard(): ");
  asserttrue(state->handCount[player] == (pre.handCount[player]-1), assertExit);
  printf(": discard 1 card - handCount is decremented by 1\n");

  printf("discardCard(): ");
  asserttrue(pre.deckCount[player] == state->deckCount[player] && memcmp(pre.deck[player], state->deck[player], sizeof(int)*MAX_DECK) == 0, assertExit);
  printf(": discard 1 card - deck is unchanged\n");

  printf("discardCard(): ");
  asserttrue(state->discardCount[player] == (pre.discardCount[player]+1), assertExit);
  printf(": discard 1 card - card is in discard pile\n");

  int i;
  int discardCount = state->handCount[player] + 1;
  for (i = 0; i < (discardCount); i++) {
    discardCard(0, player, state, 0);
  }
  printf("discardCard(): ");
  asserttrue(state->handCount[player] >= 0, assertExit);
  printf(": attempt to discard more cards than in hand - handCount is non-negative\n");
}

int main(int argc, char const *argv[]) {
  // create a game
  int seed = 1000;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, seed, &G);

  testDiscardCard(&G);
  return 0;
}
