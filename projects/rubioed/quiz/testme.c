#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    // I will randomly return all the ASCII symbols, numbers, and letters (lower & upper case)
    // to cover all the characters being checked in the testme() function.
    char a; //The returned character
    int space = 32; // ' '
    int tilde = 126; // '~'
    int range = tilde - space;
    a = (rand() % (range + 1)) + space;
    return a;
}

char *inputString()
{
    // TODO: rewrite this function
    // I will only send 5 lower case letters since that is what the testme() function is checking
    // when getting a string. At the end of the string I added the terminator '\0'
    static char string[5];
    int aa = 97; // 'a'
    int zz = 122; // 'z'
    int range = zz - aa;
    int i;
    for (i = 0; i < 5; i++) {
        string[i] = (rand() % (range + 1)) + aa;
    }
    string[5] = '\0';
    return (string);
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
