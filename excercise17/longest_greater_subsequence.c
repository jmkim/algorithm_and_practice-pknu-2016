/** Includes */
#include <stdio.h>
#include <string.h>


/** Macros */
#define MATRIX_SIZE     400
#define MAX(a,b)        ((a) > (b) ? (a) : (b))
//#define FLAG_PRINT_DEBUG


/** Global variables */
int c[MATRIX_SIZE][MATRIX_SIZE];


/** Declarations */
size_t count_convert (const int);
int lgs (const int[], const int);


/** Definitions */
int
main (void)
{
  int arr[MATRIX_SIZE] = { 0, };
  int arr_size;
  int i, j;

  printf ("n= ");
  scanf ("%d", &arr_size);

  for (i = 0; i < arr_size; ++i)
    scanf ("%d", &arr[i]);

  printf ("%d\n", count_convert (lgs (arr, arr_size)));

  return 0;
}

/** Track the LGS */
size_t
count_convert (const int max)
{
  size_t count = 1;
  int i;

  for (i = max; i > 0; i = i >> 1)
    ++count;

  return (size_t) count;
}

/** Find the Longest greater subsequence */
int
lgs (const int x[], const int x_size)
{
  int max = 0;
  int i, j, k, l;

  for (i = 1; i <= x_size; ++i)
    {
      for (j = i + 1; j <= x_size; ++j)
	{
	  if (x[i - 1] > x[j - 1])
	    c[i][j] = 0;
	  else
	    {
	      for (k = j; k >= i + 1 && x[j - 1] <= x[k - 1]; --k);

	      if (c[i][k] == 0)
		c[i][j] = 1;
	      else
		c[i][j] = c[i][k] * 2;
#ifdef FLAG_PRINT_DEBUG
	      printf ("%3d(%3d) %3d[%3d] %3d(%3d)[%3d]\n", i, x[i - 1], k,
		      c[i][k], j, x[j - 1], c[i][j - 1]);
#endif

	      if (c[i][j] > max)
		max = c[i][j];
	    }
	}
    }

  return max;
}
