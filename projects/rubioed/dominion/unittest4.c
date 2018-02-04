#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

// Original function for refernce
/*
int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;
    
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
    {
      state->coins += 1;
    }
      else if (state->hand[player][i] == silver)
    {
      state->coins += 2;
    }
      else if (state->hand[player][i] == gold)
    {
      state->coins += 3;
    }   
    }   

  //add bonus
  state->coins += bonus;

  return 0;
}
*/

// initalizeGame() prototype for refernce
// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)

int main () {
    struct gameState game;
    int numberOfPlayers = 2;
    int playerNumber = 0;
    int randomSeed = 10;
    int cards[] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int bonus = 0;
    int realReturn, shouldReturn;

    // Create a 2 player game
    initializeGame(numberOfPlayers, cards, randomSeed, &game);

    printf("Test result for updateCoins():\n");
    printf("updateCoins(): ");
    shouldReturn = 4;
    updateCoins(playerNumber, &game, bonus);
    realReturn = game.coins;
    printf("%s", (realReturn == shouldReturn) ? "PASS there is 4 coins in inital hand.\n" : "FAIL since there is no 4 coins in the inital hand.\n");
    
    // change player 0 hand to 1 gold, 1 silver, 2 copper, 2 bonus
    game.hand[playerNumber][0] = gold;
    game.hand[playerNumber][1] = silver;
    bonus = 2;

    printf("updateCoins(): ");
    shouldReturn = 9;
    updateCoins(playerNumber, &game, bonus);
    realReturn = game.coins;
    printf("%s", (realReturn == shouldReturn) ? "PASS since it returned 9 coins.\n" : "FAIL since it did not return 9 coins.\n");

    return 0;
}