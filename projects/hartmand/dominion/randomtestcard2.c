/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE: 2018-02-18
 * PROJECT: Assignment 4
 * DESCRIPTION: Village
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "asserttrue.h"

#define NUM_TESTS 250000
#define ASSERT_EXIT 0
#define NUM_CARDS 27

// Produces a random number from min up to and including max
int randInt(int min, int max) {
  int range = max + 1 - min;
  return (rand() % range) + min;
}

void showStateDiffs(int player, struct gameState *s1, struct gameState *s2) {
  printf("HandCount - State1: %d | State2: %d\n", s1->handCount[player], s2->handCount[player]);
  printf("DeckCount - State1: %d | State2: %d\n", s1->deckCount[player], s2->deckCount[player]);
  printf("DiscardCount - State1: %d | State2: %d\n", s1->discardCount[player], s2->discardCount[player]);
}

void testVillage() {
  struct gameState pre, game;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
  int i, j, k, p;  // loop vars
  int player;
  int cardsDrawn, cardsPlayed;
  int handPos;
  int didNotBreak;
  int testsFailed = 0;

  for (i = 0; i < NUM_TESTS; i++) {
    initializeGame(randInt(2,MAX_PLAYERS), kingdomCards, rand(), &game);

    // Randomize Stuff
    player = game.whoseTurn = randInt(0, game.numPlayers-1);
    for (j = 0; j < game.numPlayers; j++) {
      // Randomize hand. Leave room to draw cards if it's the current player
      game.handCount[j] = j == player ? randInt(0, MAX_HAND-2): randInt(0, MAX_HAND);
      for (k = 0; k < game.handCount[j]; k++) {
        game.hand[j][k] = randInt(0, NUM_CARDS-1);
      }

      // Randomize deck
      game.deckCount[j] = randInt(0, MAX_DECK);
      for (k = 0; k < game.deckCount[j]; k++) {
        game.deck[j][k] = randInt(0, NUM_CARDS-1);
      }

      // Randomize discard. Leave room to discard if it's the current player
      game.discardCount[j] = j == player ? randInt(0, MAX_DECK-1): randInt(0, MAX_DECK);
      for (k = 0; k < game.discardCount[j]; k++) {
        game.discard[j][k] = randInt(0, NUM_CARDS-1);
      }

      // Randomize num of actions
      game.numActions = INT_MAX - 2;
    }

    // Put village into player's hand
    gainCard(village, &game, 2, player); // 2 is toHand
    memcpy(&pre, &game, sizeof(struct gameState));

    villageAction(player, &game, game.handCount[player]-1);

    // Test 1 card was played
    cardsPlayed = game.playedCardCount - pre.playedCardCount;
    if(asserttrue(cardsPlayed == 1, ASSERT_EXIT) == 0)
      testsFailed++;
    printf(": one card was played\n");

    // Test player's hand
    cardsDrawn = (game.handCount[player] - pre.handCount[player]) + (cardsPlayed);
    if (asserttrue(cardsDrawn == 1, ASSERT_EXIT) == 0) {
      testsFailed++;
      showStateDiffs(player, &pre, &game);
    }
    printf(": player %d - 1 cards drawn (and 1 card discarded)\n", player);

    // Test 2 actions were added
    pre.numActions += 2;
    if (asserttrue(pre.numActions == game.numActions, ASSERT_EXIT) == 0) {
      testsFailed++;
    }
    printf(": player %d - 2 actions were added\n", player);

    // Simulate village played on pre hand
    handPos = pre.handCount[player] - 1;
    didNotBreak = 1;
    for (j = 0; j < cardsDrawn; j++) {
      if (pre.deckCount[player] > 0) {
        drawCard(player, &pre);
      }
      // Deck was shuffled - set hand, deck, discard, and playedCards according
      else {
        memcpy(pre.hand[player], game.hand[player], sizeof(int)*MAX_HAND);
        pre.handCount[player] = game.handCount[player];
        memcpy(pre.deck[player], game.deck[player], sizeof(int)*MAX_DECK);
        pre.deckCount[player] = game.deckCount[player];
        memcpy(pre.discard[player], game.discard[player], sizeof(int)*MAX_DECK);
        pre.discardCount[player] = game.discardCount[player];
        memcpy(pre.playedCards, game.playedCards, sizeof(int)*MAX_DECK);
        pre.playedCardCount = game.playedCardCount;

        didNotBreak = 0;
        break;
      }
    }
    if (didNotBreak) {
      discardCard(handPos, player, &pre, 0);
      if (asserttrue( (pre.handCount[player] == game.handCount[player]) && (memcmp(&pre.hand[player], &game.hand[player], sizeof(int) * MAX_HAND) == 0), ASSERT_EXIT) == 0)
        testsFailed++;
      printf(": all cards were drawn from player %d's deck\n", player);
    }

    // Test other players hand
    for (p = 0; p < game.numPlayers; p++) {
      if (p != player) {
        if (asserttrue( (pre.handCount[p] == game.handCount[p]) && (memcmp(&pre.hand[p], &game.hand[p], sizeof(int) * MAX_HAND) == 0), ASSERT_EXIT) == 0)
          testsFailed++;
        printf(": player %d's hand didn't change.\n", p);
      }
    }

    // Test rest of game statement
    if (asserttrue((memcmp(&pre, &game, sizeof(struct gameState)) == 0), ASSERT_EXIT) == 0)
      testsFailed++;
    printf(": rest of gameState is as it should be\n");
  }
  printf("\nTest(s) Failed: %d\n\n", testsFailed);
}


int main(int argc, char *argv[]) {
    srand(time(NULL));

    testVillage();

    return 0;
}
