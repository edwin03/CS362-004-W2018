/******************************************************************************
 * AUTHOR: David Hartman
 * CLASS: CS362
 * DATE; 2018-02-04
 * PROJECT: Assignment 3
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/******************************************************************************
 * NAME: asserttrue
 * DESCRIPTION: Takes a result and tests whether or not that result
 *   is true and optionally exits the program if it isn't.
 ******************************************************************************/
int asserttrue(int test, int exitOnFail) {
  if (test)
    printf("PASS");
  else
    printf("FAIL");

  if (!test && exitOnFail)
    exit(1);

  return test;
}
