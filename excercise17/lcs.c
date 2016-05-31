/** Includes */
#include <stdio.h>
#include <string.h>


/** Macros */
#define MATRIX_SIZE     400
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
//#define FLAG_PRINT_DEBUG_LEVEL_1
//#define FLAG_PRINT_DEBUG_LEVEL_2


/** Global variables */
int c[MATRIX_SIZE][MATRIX_SIZE];


/** Declarations */
size_t backtrack (const char[], const char[], const int, const int);
int lcs (const char[], const char[]);


/** Definitions */
int
main (void)
{
  char a[MATRIX_SIZE] = { 0, };
  char b[MATRIX_SIZE] = { 0, };
  int i, j;

  printf ("Enter a= ");
  scanf ("%s", a);

  printf ("Enter b= ");
  scanf ("%s", b);

  lcs (a, b);

#if defined(FLAG_PRINT_DEBUG_LEVEL_1) || defined(FLAG_PRINT_DEBUG_LEVEL_2)
  printf ("   ");

  for (i = 1; i <= strlen (b); ++i)
    printf ("%2c ", b[i - 1]);

  printf ("\n");

  for (i = 1; i <= strlen (a); ++i)
    {
      printf ("%2c ", a[i - 1]);

      for (j = 1; j <= strlen (b); ++j)
	printf ("%2d ", c[i][j]);

      printf ("\n");
    }
  printf ("\n");
#endif

  printf ("\n%d \n", backtrack (a, b, strlen (a), strlen (b)));

  return 0;
}

/** Track the LCS */
size_t
backtrack (const char a[], const char b[], const int i, const int j)
{
  size_t count = 0;

  if (i < 1 || j < 1)
    return count;

  if (c[i][j] == c[i - 1][j])
#ifdef FLAG_PRINT_DEBUG_LEVEL_2
    {
      printf ("case 1: %d %d -> %d %d\n", i, j, i - 1, j);
      return backtrack (a, b, i - 1, j);
    }
  else if (c[i][j] == c[i][j - 1])
    {
      printf ("case 2: %d %d -> %d %d\n", i, j, i, j - 1);
      return backtrack (a, b, i, j - 1);
    }
  else
    {
      printf ("case 3: %d %d -> %d %d\n", i, j, i - 1, j - 1);
      count = backtrack (a, b, i - 1, j - 1);
      printf ("a: %c\n", a[i - 1]);
      printf ("b: %c\n", b[j - 1]);

      return count + 1;
    }
#else
    return backtrack (a, b, i - 1, j);
  else if (c[i][j] == c[i][j - 1])
    return backtrack (a, b, i, j - 1);
  else
    {
      count = backtrack (a, b, i - 1, j - 1);
      printf ("%c", a[i - 1]);

      return count + 1;
    }
#endif
}


/** Find the Longest common subsequence */
int
lcs (const char a[], const char b[])
{
  int a_size = strlen (a);
  int b_size = strlen (b);
  printf ("%d %d\n", a_size, b_size);
  int i, j;

  for (i = 0; i <= a_size; ++i)
    c[i][0] = 0;

  for (j = 0; j <= b_size; ++j)
    c[0][j] = 0;

  for (i = 1; i <= a_size; ++i)
    {
      for (j = 1; j <= b_size; ++j)
	{
	  if (a[i - 1] == b[j - 1])
	    c[i][j] = c[i - 1][j - 1] + 1;
	  else
	    {
	      c[i][j] = MAX (c[i - 1][j], c[i][j - 1]);
	    }
	}
    }

  return c[a_size][b_size];
}
