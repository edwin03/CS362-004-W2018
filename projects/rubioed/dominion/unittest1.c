#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include "rngs.h"

// Original function for refernce
/*
int getCost(int cardNumber)
{
  switch( cardNumber ) 
    {
    case curse:
      return 0;
    case estate:
      return 2;
    case duchy:
      return 5;
    case province:
      return 8;
    case copper:
      return 0;
    case silver:
      return 3;
    case gold:
      return 6;
    case adventurer:
      return 6;
    case council_room:
      return 5;
    case feast:
      return 4;
    case gardens:
      return 4;
    case mine:
      return 5;
    case remodel:
      return 4;
    case smithy:
      return 4;
    case village:
      return 3;
    case baron:
      return 4;
    case great_hall:
      return 3;
    case minion:
      return 5;
    case steward:
      return 3;
    case tribute:
      return 5;
    case ambassador:
      return 3;
    case cutpurse:
      return 4;
    case embargo: 
      return 2;
    case outpost:
      return 5;
    case salvager:
      return 4;
    case sea_hag:
      return 4;
    case treasure_map:
      return 4;
    }
    
  return -1;
}
*/

int main () {
    // Each card cost
    int curse = 0, estate = 2, duchy = 5, province = 8, copper = 0, silver = 3, gold = 6, adventurer = 6, council_room = 5, feast = 4, gardens = 4, mine = 5, remodel = 4;
    int smithy = 4, village = 3, baron = 4, great_hall = 3, minion = 5, steward = 3, tribute = 5, ambassador = 3, cutpurse = 4, embargo = 2, outpost = 5, salvager = 4;
    int sea_hag = 4, treasure_map = 4; 
    int costs[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
    int i; 
    int shouldReturn; 
    int realReturn;
    int numberCards = 27; //treasure_map + 1
    int noMatch = 0;

    srand(time(NULL));

    printf("Test result for getCost():\n");

    for (i = 0; i < numberCards; i++) {
    	realReturn = getCost(i);
    	shouldReturn = costs[i];
        if (shouldReturn != realReturn) {
        	noMatch = 1;
        	break;
        }
    }

    if (noMatch > 0) {
	printf("getCost(): FAIL since card number %d, should have return %d but this function returned %d.\n", i, shouldReturn, realReturn);
    } 
    else {
	printf("getCost(): PASS all card returned the correct cost.\n");
    }

    // Generate a random number from 30 to 100.
    i = rand() % 100 + 30;
    realReturn = getCost(i);
    if (-1 != realReturn) {
	printf("getCost(): FAIL since card number %d, does not exist so it should of return %d.\n", i, -1);
    } 
    else {
	printf("getCost(): PASS since it returned -1.\n");
    }

    return 0;
}