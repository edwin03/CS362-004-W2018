#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

// Original function for refernce
/*
    int isGameOver(struct gameState *state) {
      int i;
      int j;
        
      //if stack of Province cards is empty, the game ends
      if (state->supplyCount[province] == 0)
        {
          return 1;
        }
      //if three supply pile are at 0, the game ends
      j = 0;
      for (i = 0; i < 25; i++)
        {
          if (state->supplyCount[i] == 0)
          {
            j++;
          }
        }
      if ( j >= 3)
        {
          return 1;
        }
      return 0;
    }
*/
int main () {
    int i;
    struct gameState game;
    int realReturn;
    int shouldReturn;

    printf("Test result for isGameOver():\n");

    // Start all supply piles with one card
    for (i = 0; i < 25; i++)
	game.supplyCount[i] = 1;

    // Test 1
    printf("isGameOver(): ");
    shouldReturn = 0;
    realReturn = isGameOver(&game);
    printf("%s", (realReturn == shouldReturn) ? "PASS when there is no empty piles GAME CONTINUE\n" : "FAIL to return 0 since there is no empty piles\n");

    // Test 2
    printf("isGameOver(): ");
    shouldReturn = 1;
    game.supplyCount[province] = 0;
    realReturn = isGameOver(&game);
    printf("%s", (realReturn == shouldReturn) ? "PASS when there's no province card and there is 1 card in each pile GAME END.\n" : "FAIL to return 1 since thers is no province card.\n");

    // Test 2
    printf("isGameOver(): ");
    shouldReturn = 1;
    game.supplyCount[province] = 1;
    game.supplyCount[baron] = game.supplyCount[remodel] = game.supplyCount[feast] = 0;
    realReturn = isGameOver(&game);
    printf("%s", (realReturn == shouldReturn) ? "PASS when there is 3 empty piles GAME END.\n" : "FAIL to return 1 since there are three empty piles.\n");

    

    return 0;
}