// Edwin Rubio
// 02/16/2018
// CS362 - OSU
// File Name: randomtestcard2.c
// Instructions: Write an automed random test generator for three Dominion cards "use the refactored code
// you created for assignement-2", one of them being the adventurer card, and at least one being a card 
// you wrote unit tests for in assignemnt-3. Check these testers in as randomtestcard1.c, 
// randomtestcard2.c, and randomtestadventurer.c.
// council room card info: +4 cards, +1 buy.  Each other player draws a card. 
/*
council_roomCard() function:
void council_roomCard (int currentPlayer, struct gameState *state, int handPos)
{
  int i;//I added this here...
  //+4 Cards
  for (i = 0; i < 4; i++)
  {
    drawCard(currentPlayer, state);
  }
              
  //+1 Buy
  state->numBuys++;
              
  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++)
  {
    if ( i != currentPlayer )
    {
      drawCard(i, state);
    }
    i++;//I introduced this bug here, this will skip half of the players. First player will draw a card, then second wont, then 3rd will draw, etc.
  }
              
  //put played card in played card pile
  discardCard(handPos, currentPlayer, state, 0);
}
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>// rand(), srand()
#include <time.h>// time()
#include <string.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"// Random()

#define TESTCARD "council_room"

int main() 
{
	// as seen in the playdom.c file in line 88
    int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
	int discardCardFails = 0;
	int test;
	int i, x, n;
	int cEFunctionFailed = 0;// cardEffect function fails
	int handCountFailed = 0;
	int totalCards = 0, copytotalCards = 0, deckTotalFailed = 0, buyFails = 0;
	int playersHandNotMatch = 0;
	int playerHand[4];
    int copyPlayerHand[4];

	// variables to hold previous and post state of the game.
	struct gameState G, testG;
	
	//seed rand()
	srand(time(0));

	printf("----------------- Starting Random Test! ----------------\n");
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	for (i = 0; i < 250; i++)
	{
		// Set a random game state on G
		for (x = 0; x < sizeof(struct gameState); x++)
		{
			((char*)&G)[x] = rand() * 256;
		}

		// Set a random game configuration
		// Set the number of players where the max is 4 and the min is 2
		G.numPlayers = rand() % (4 + 1 - 2) + 2;
		// Select the current player
		G.whoseTurn = rand() % G.numPlayers;
		// Add +1 buy as the card specifies it
		G.numBuys = 0;
		// Assign the count deck for the player that is currently playing
		G.deckCount[G.whoseTurn] = rand() % (MAX_DECK - 3 + 1) + 3;
		// Assign the  hand count for the player that is currently playing
		G.handCount[G.whoseTurn] = rand() % (MAX_HAND - 3 + 1) + 3;
		// Set randomly the number of discarded cards
		G.discardCount[G.whoseTurn] = rand() % (MAX_DECK - 3 + 1) + 3;
		// Now lets choose a card from the hand deck
		handpos = rand() % G.handCount[G.whoseTurn];

		// copy the game state to a test case before calling the cardEffect
		memcpy(&testG, &G, sizeof(struct gameState));

		// Test the cardEffect() function
		test = cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
        if (test != 0) {
            printf("cardEffect function failed");
            cEFunctionFailed++;
        };

        // Check the hand count
        if ((testG.handCount[G.whoseTurn]) != G.handCount[G.whoseTurn] + 4 - 1)
        {
        	printf("Failed: Hand Count: %d, Expected: %d \n\n", testG.handCount[G.whoseTurn], G.handCount[G.whoseTurn]+ 4 -1);
        	handCountFailed++;
        }

        // Check to see if the total deck cards is the same
        totalCards = G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn];
		copytotalCards = testG.deckCount[G.whoseTurn] + testG.discardCount[G.whoseTurn];
		if (copytotalCards != totalCards - 4) 
		{
			printf("Failed: Total Cards: %d, Expected: %d \n\n", copytotalCards, totalCards-4);
			deckTotalFailed++;
		}

		// test buys using state struct
		if (testG.numBuys != G.numBuys + 1) 
		{
	        printf("Failed: Buy Count: %d, Expected: %d \n\n", testG.numBuys, G.numBuys+1);
	        buyFails++;
        
	    }

		// confirm that each player got a card
	    for (n = 0; n < G.numPlayers; n++) 
	    {
          if (n != G.whoseTurn) 
          {
	          copyPlayerHand[n] = testG.handCount[n];
	          playerHand[n] = G.handCount[n];

          }
        }

	    for (n = 0; n < G.numPlayers; n++) 
	    {
            if (n != G.whoseTurn) 
            {
                if (copyPlayerHand[n] != playerHand[n] + 1) 
                {
					printf("Failed: Other Player Hand Count: %d, Expected: %d \n\n", copyPlayerHand[n],  playerHand[n] + 1);
					playersHandNotMatch++;
                }
            }
        }
	}

	if (cEFunctionFailed == 0 && handCountFailed == 0 && deckTotalFailed == 0 && buyFails == 0 && playersHandNotMatch == 0) 
	{
        printf("----NO ERRORS FOUND----\n");
    } 
    else
    {
        printf("----Failed----\n");
        printf("cardEffect () function fails: %d\n", cEFunctionFailed);
        printf("Hand count fails: %d\n", handCountFailed);
        printf("Deck total fails: %d\n", discardCardFails);
        printf("Buy fails: %d\n", buyFails);
        printf("Players hand count do not match fails: %d\n", playersHandNotMatch);
    }

    return 0;

}