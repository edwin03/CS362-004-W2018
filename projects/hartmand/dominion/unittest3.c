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

void testWhoseTurn(struct gameState *state) {
  // Store a copy of the gameState before the card is played
  struct gameState pre;
  memcpy (&pre, state, sizeof(struct gameState));

  int firstPlayer = whoseTurn(state);
  int oldPlayer = firstPlayer;
  int newPlayer;

  int i;
  for (i = 0; i < state->numPlayers; i++) {
    endTurn(state);
    newPlayer = whoseTurn(state);
    printf("whoseTurn(): ");
    asserttrue(oldPlayer != newPlayer, assertExit);
    printf(": new turn player %d != previous turn player %d\n", newPlayer, oldPlayer);
    oldPlayer = newPlayer;
  }
  printf("whoseTurn(): ");
  asserttrue(firstPlayer == newPlayer, assertExit);
  printf(": back to first player %d\n", firstPlayer);
}

int main(int argc, char const *argv[]) {
  // create a game
  int seed = 1000;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, seed, &G);

  testWhoseTurn(&G);
  return 0;
}
