#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <math.h>
#include "rngs.h"

// Original function for refernce
/*
int whoseTurn(struct gameState *state) {
  return state->whoseTurn;
}
*/

int main () {

	struct gameState game;
	int turn = 0;
	//int currentTurn = 0;
	int shouldReturn;
	int realReturn;

    printf("Test result for whoseTurn():\n");
    printf("whoseTurn(): ");
    shouldReturn = 0;
    game.whoseTurn = turn;
    realReturn = whoseTurn(&game);
    printf("%s", (realReturn == shouldReturn) ? "PASS since it is player 0 turns.\n" : "FAIL fail since it did not aggree that it was player 0 turn.\n");
    
    // Changed game turn to player 1
    turn = 1;
	game.whoseTurn = turn;

    printf("whoseTurn(): ");
    shouldReturn = turn;
    realReturn = whoseTurn(&game);
    printf("%s", (realReturn == shouldReturn) ? "PASS since it is player 1 turns.\n" : "FAIL fail since it did not aggree that it was player 1 turn.\n");

    return 0;
}