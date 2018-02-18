// Edwin Rubio
// 02/15/2018
// CS362 - OSU
// File Name: randomtestcard1.c
// Instructions: Write an automed random test generator for three Dominion cards "use the refactored code
// you created for assignement-2", one of them being the adventurer card, and at least one being a card 
// you wrote unit tests for in assignemnt-3. Check these testers in as randomtestcard1.c, 
// randomtestcard2.c, and randomtestadventurer.c.
// smithy card info: action card and add 3 cards

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>// rand(), srand()
#include <time.h>// time()
#include <string.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"// Random()

#define TESTCARD "smithy"

int main() 
{
	// as seen in the playdom.c file in line 43
    int handPos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
	int discardCardFails = 0;
	int test;
	int i, x;
	int d1, d2, d3; // draw cards
	int dCTest;
	int dCardFunctionFailed = 0;// drawCard function fails
	int cEFunctionFailed = 0;// cardEffect function fails
	int handCount, testHandCount;
	int deckCount, testDeckCount;
	int handCountFailed = 0;
	int deckCountFails = 0;

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
		// Assign the count deck for the player that is currently playing
		G.deckCount[G.whoseTurn] = rand() % (MAX_DECK - 3 + 1) + 3;
		// Assign the  hand count for the player that is currently playing
		G.handCount[G.whoseTurn] = rand() % (MAX_HAND - 3 + 1) + 3;
		// Set randomly the number of discarded cards
		G.discardCount[G.whoseTurn] = rand() % (MAX_DECK - 3 + 1) + 3;
		// Now lets choose a card from the hand deck
		handPos = rand() % G.handCount[G.whoseTurn];

		// copy the game state to a test case before calling the cardEffect
		memcpy(&testG, &G, sizeof(struct gameState));

		// Now lets call the cardEffect function with the smithy card
		test = cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

		// get 3 cards
		// Draw cards manually using the manually initizalied game state
		d1 = drawCard(G.whoseTurn, &G); 
		d2 = drawCard(G.whoseTurn, &G);
		d3 = drawCard(G.whoseTurn, &G);
		
		// Check to see if drawCard() function returned -1 (error)
		//You left here!!!!!!!
		if (d1 == -1 || d2 == -1 || d3 == -1)
		{
			dCardFunctionFailed++;
		}

		//discard card from hand (line 656 in dominion.c)
    	dCTest = discardCard(handPos, G.whoseTurn, &G, 0);

    	//Check to see if the dicardCard() function failed
    	if(dCTest != 0)
    	{
    		discardCardFails++;
    	}
    	
    	// Check to see if the cardEffect() function failed. It returns
    	// -1.
    	if (test != 0)
    	{
    		cEFunctionFailed++;
    	}

    	// Now check to see if the hand count do not match.
    	handCount = G.handCount[G.whoseTurn];
    	testHandCount = testG.handCount[G.whoseTurn];
    	if (handCount != testHandCount)
    	{
    		handCountFailed++;
    	}

    	// Now check to see if the deck count do not match
    	deckCount = G.deckCount[G.whoseTurn];
    	testDeckCount = testG.deckCount[G.whoseTurn];
    	if (deckCount != testDeckCount)
    	{
    		deckCountFails++;
    	}
	}

	if (dCardFunctionFailed == 0 && discardCardFails == 0 && cEFunctionFailed == 0 && handCountFailed == 0 && deckCountFails == 0) 
	{
        printf("----NO ERRORS FOUND----\n");
    } 
    else
    {
        printf("----Failed----\n");
        printf("cardEffect () function fails: %d\n", cEFunctionFailed);
        printf("drawCard () function fails: %d\n", dCardFunctionFailed);
        printf("discardCard() function fails: %d\n", discardCardFails);
        printf("Hand count fails: %d\n", handCountFailed);
        printf("Deck count fails: %d\n", deckCountFails);
    }

	return 0;
}