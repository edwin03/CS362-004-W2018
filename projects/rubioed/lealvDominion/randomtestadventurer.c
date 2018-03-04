// Edwin Rubio
// 02/14/2018
// CS362 - OSU
// File Name: randomtestadventurer.c
// Instructions: Write an automed random test generator for three Dominion cards "use the refactored code
// you created for assignement-2", one of them being the adventurer card, and at least one being a card 
// you wrote unit tests for in assignemnt-3. Check these testers in as randomtestcard1.c, 
// randomtestcard2.c, and randomtestadventurer.c.

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>// rand(), srand()
#include <time.h>// time()
#include <string.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"// Random()

#define TESTCARD "adventurer"

int main() {
	// variables to hold previous and post state of the game.
	struct gameState G, testG;
	// as seen in the playdom.c file in line 88
    int handPos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
    //requires to add 2 treasure cards to the hand deck
    int newCards = 2;
    int i, x, y, m, a;
    int test;
	int tCount = 0;// Treasure count
	int tCount2 = 0;// Treasure count
	int dCardFunctionFailed = 0, handCountFailed = 0, cEFunctionFailed = 0, deckCountFails = 0;
	int treasureCountFailed = 0;

	//int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
	//int thisPlayer = 0;
	//int remove1, remove2;

	// Seeding the srand function with the current time
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
		// Now lets add some treasure cards to the hand deck of the current player.
		for (x = 0; x < G.handCount[G.whoseTurn]; x++)
		{
			y = rand() % 2;
			if (y == 1)
				G.hand[G.whoseTurn][x] = copper;
			else
				G.hand[G.whoseTurn][x] = estate;
		}

		for (x = 0; x < G.deckCount[G.whoseTurn]; x++)
		{
			y = rand() % 2;
			if (y == 1)
				G.deck[G.whoseTurn][x] = copper;
			else
				G.deck[G.whoseTurn][x] = estate;
		}

		// copy the game state to a test case before calling the cardEffect
		memcpy(&testG, &G, sizeof(struct gameState));

		// Test to see if the adventurerCard was called
        test = cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
        if (test != 0) {
            printf("cardEffect function failed");
            cEFunctionFailed++;
        };

        // Check the hand count
        if ((testG.handCount[G.whoseTurn]) != G.handCount[G.whoseTurn] + newCards)
        {
        	printf("Failed: Hand Count: %d, Expected: %d \n\n", testG.handCount[G.whoseTurn], G.handCount[G.whoseTurn]+newCards);
        	dCardFunctionFailed++;
        	handCountFailed++;
        }

        // Check the deck and discard count
        if ((G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn]) - newCards != (testG.deckCount[G.whoseTurn] + testG.discardCount[G.whoseTurn]))
        {
        	printf("Total Cards: %d, Expected: %d \n\n", (testG.deckCount[G.whoseTurn] + testG.discardCount[G.whoseTurn]), (G.deckCount[G.whoseTurn] + G.discardCount[G.whoseTurn]) - newCards);
        	deckCountFails++;
        }

      	//---------- Now lets test the treasure counts ----------//
        // Lets look at the orginal game state first
        
        // Get the number of cards that the current player holds
        m = numHandCards(&G);
        a = 0;

        while (a < m)
        {
        	if (handCard(a, &G) == copper)
        	{
        		tCount = tCount + 1;
        	}
        	else if (handCard(a, &G) == silver)
        	{
        		tCount = tCount + 2;
        	}
        	else if (handCard(a, &G) == gold)
        	{
        		tCount = tCount + 3;
        	}
        	a++;
        }

        m = numHandCards(&testG);
        a = 0;

        while (a < m)
        {
        	if (handCard(a, &testG) == copper)
        	{
        		tCount2 = tCount2 + 1;
        	}
        	else if (handCard(a, &testG) == silver)
        	{
        		tCount2 = tCount2 + 2;
        	}
        	else if (handCard(a, &testG) == gold)
        	{
        		tCount2 = tCount2 + 3;
        	}
        	a++;
        }

        if (tCount != tCount2 + 2)
        {
        	printf("Teeasure Count: %d, Expected Treasure Count: >= %d \n\n", tCount2, tCount + 2);	
        	treasureCountFailed++;
        }
 
	}

	if (cEFunctionFailed == 0 && dCardFunctionFailed == 0 && handCountFailed == 0 && deckCountFails == 0 && treasureCountFailed == 0) 
	{
        printf("----NO ERRORS FOUND----\n");
    } 
    else
    {
        printf("----Failed----\n");
        printf("cardEffect () function fails: %d\n", cEFunctionFailed);
        printf("drawCard () function fails: %d\n", dCardFunctionFailed);
        printf("Hand count fails: %d\n", handCountFailed);
        printf("Deck count fails: %d\n", deckCountFails);
		printf("Treasure Count fails: %d\n", treasureCountFailed);
    }

    return 0;
}