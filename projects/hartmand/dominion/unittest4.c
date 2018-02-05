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

void testFullDeckCount(struct gameState *state) {
  // Store a copy of the gameState before the card is played
  struct gameState pre;
  memcpy (&pre, state, sizeof(struct gameState));

  int player = whoseTurn(state);

  printf("fullDeckCount(): ");
  // Add a copper to discard for current player
  gainCard(copper, state, 0, player);
  // Add a copper to deck for current player
  gainCard(copper, state, 1, player);
  // Add a copper to hand for current player
  gainCard(copper, state, 2, player);
  asserttrue(fullDeckCount(player, copper, state) == fullDeckCount(player, copper, &pre) + 3, assertExit);
  printf(": add a copper to discard, deck, and hand and check that the number of copper for the current player went up 3\n");

  printf("fullDeckCount(): ");
  int opponent = player + 1;
  if (opponent >= state->numPlayers)
    opponent = 0;
  // Add a copper to the hand of the opponent
  gainCard(copper, state, 1, opponent);
  asserttrue(fullDeckCount(player, copper, state) == fullDeckCount(player, copper, &pre) + 3, assertExit);
  printf(": add a copper to the hand of an opponent and make sure it didn't raise the current players copper count.\n");
}

int main(int argc, char const *argv[]) {
  // create a game
  int seed = 1000;
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  initializeGame(2, k, seed, &G);

  testFullDeckCount(&G);
  return 0;
}
